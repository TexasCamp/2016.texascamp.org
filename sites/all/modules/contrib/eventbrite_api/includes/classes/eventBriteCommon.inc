<?php
/**
 * @file
 * Contains eventBriteCommon.
 *
 * This class actuall makes the API calls and is referenced by the other classes
 */

class eventBriteCommon {

  private $op;
  private $op_type;
  private $userKey;
  private $appKey;
  private $allowed_cache;
  public $params = array();
  private $module;
  private $forceNoCache;
  private $query_string;
  private $server;
  private $dataOverride;
  private $accessToken;

  function __construct($op, $op_type, $dataOverride = '', $forceNoCache = FALSE, $userKey = null, $appKey = null, $accessToken = null) {
    $this->op = $op;
    $this->op_type = $op_type;
    $defaultacct = variable_get('eventbrite_api_defaultacct', array('api_userkey' => '', 'api_appkey' => '', 'api_oauth' => '', 'api_name' => ''));
    if (!empty($userKey)) {
      $this->userKey = $userKey;
    }
    else{
      $this->userKey = $defaultacct['api_userkey'];
    }
    if (!empty($appKey)) {
      $this->appKey = $appKey;
    }
    else {
      $this->appKey = $defaultacct['api_appkey'];
    }
    if (!$this->userKey || !$this->appKey) {
      drupal_set_message(t('Your EventBrite keys have not been set. Please set them on the ') . l('admin screen.', 'admin/config/services/eventbrite'), 'error');
      $watchdog_message = t('eventBriteCommon __construct was called and returned false.' . "\n");
      $watchdog_message .= t('Verify that valid authentication keys have been entered.' . "\n");
      watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
    $this->allowed_cache = ($this->op_type == 'get') ? 60 * variable_get('eventbrite_cache_minimum', 5) : 0;
    $this->module = 'eventbrite';
    $this->forceNoCache = $forceNoCache;
    if ($dataOverride == ''){
      $this->server = variable_get('eventbrite_server', 'https://www.eventbrite.com/json/');
    }
    else {
      $this->server = $dataOverride;
    }
    if (!empty($accessToken)) {
      $this->accessToken = $accessToken;
    }
    else {
      $this->accessToken = $defaultacct['api_oauth'];
    }
  }

  /**
   * processJSONRequest
   *
   * Make the requested call to the API and return a JSON object
   *
   * @param bool $this
   *   If this is a version 3 API call, then change the structure of the request
   * @return object
   *   A JSON object represeting the returned values from the API call
   */
  public function processJSONRequest($v3 = FALSE) {
    // Invoke hook_eventbrite_request_alter for sub modules to make changes
    // Do not invoke for user_get calls, user_get should never be altered
    if (!$this->appKey) {
      drupal_set_message(t('Your EventBrite keys have not been set. Please set them on the ') . l('admin screen.', 'admin/config/services/eventbrite'), 'error');
      $watchdog_message = t('eventBriteCommon __construct was called and returned false.' . "\n");
      $watchdog_message .= t('Verify that valid authentication keys have been entered.' . "\n");
      watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_ERROR);
      return FALSE;
    }

    if (isset($this->params['id'])) {
      $id = $this->params['id'];
    }
    else {
      $id = isset($this->params['email']) ? $this->params['email'] : '';
    }

    // Build the querystring from the params
    $param_list = array();
    $this->params['user_key'] = $this->userKey;
    $this->params['app_key'] = $this->appKey;
    foreach ($this->params as $key => $value) {
      $param_list[] = $key . '=' . urlencode($value);
    }
    $this->query_string = join('&', $param_list);

    switch ($this->op) {
      case 'user_get':
        break;
      default:
        // Manually call each hook here since module_invoke_all doesn't support hooks with references as params
        foreach (module_implements('eventbrite_api_request_alter') as $module) {
          $function = $module . '_eventbrite_api_request_alter';
          $function($this);
        }
        break;
    }

    // Check cache, if there is something there and it is recent enough then use it
    // Otherwise make a call to the Eventbrite server
    if ($this->op_type == 'get' && $this->allowed_cache) {
      if (!$this->forceNoCache && $cache = cache_get('eventBriteCommon' . $this->op . '_' . $id . '_' .$this->query_string, 'cache_eventbrite')) {
        if (variable_get('eventbrite_debug', 0)) {
          drupal_set_message(
            t('From cache. Op: !op. Query String: !query',
            array('!op' => $this->op, '!query' => $this->query_string)
          ));
        }
        $return = drupal_json_decode($cache->data);
        $return['source'] = 'cache';
        return $return;
      }
    }

    if (variable_get('eventbrite_debug', 0)) {
      drupal_set_message(
        t($this->server. '!op?!query',
        array('!op' => $this->op, '!query' => $this->query_string))
      );
    }

    // Send HTTP request to the server - since we don't have cached data
    if ($v3) {
      $id = isset($this->params['id']) ? $this->params['id'] : '';
      $req_string = $this->server . $id . '/' . $this->op . '?token=' . $this->accessToken;
    } else {
      $req_string = $this->server . $this->op . '?' . $this->query_string;
    }
    if ($result = drupal_http_request($req_string) ) {
      if ($return = $this->processResult($result)) {
        $return = drupal_json_decode($return);
        // If error type is set, log to watchdog
        if (isset($return['error_message'])) {
          $watchdog_message = t('Error type: !error_type', array('!error_type' => $return['error_type'])) . "\n";
          $watchdog_message .= t('Error msg: !error_message', array('!error_message' => $return['error_message'])) . "\n";
          $watchdog_message .= t('Request: !request', array('!request' => $result->request)) . "\n";
          watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_WARNING);
          drupal_set_message(t(
            'EventBrite is unable to process your request.' . "\n" . 'Error Type: !errortype.' . "\n" . 'Error Messsage !error.' . "\n" . '' . "\n" . 'See the error log for more details or contact your administrator.',
            array('!error_type' => $return['error_type'], '!error_message' => $return['error_message'])
            ), 'error');
          return FALSE;
        }
        if ($this->op_type == 'get') {
          // store the returned string in the cache
          cache_set('eventBriteCommon' . $this->op . '_' . $id . '_' .$this->query_string, $return, 'cache_eventbrite', time() + $this->allowed_cache);
        }
        $return['source'] = 'server';
      }
      return $return;
    }

  }

  /**
   * Function processXMLRequest
   *
   *
   * @param  [type] $this [description]
   * @return [type]          [description]
   */
  public function processXMLRequest() {
    // Invoke hook_eventbrite_request_alter for sub modules to make changes
    // Do not invoke for user_get calls, user_get should never be altered
    if (!$this->appKey) {
      drupal_set_message(t('Your EventBrite keys have not been set. Please set them on the ') . l('admin screen.', 'admin/config/services/eventbrite'), 'error');
      $watchdog_message = t('eventBriteCommon __construct was called and returned false.' . "\n");
      $watchdog_message .= t('Verify that valid authentication keys have been entered.' . "\n");
      watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_ERROR);
      return FALSE;
    }

    // Invoke hook_eventbrite_request_alter for sub modules to make changes
    // Do not invoke for user_get calls, user_get should never be altered
    switch ($this->op) {
      case 'user_get':
        break;
      default:
        // Manually call each hook here since module_invoke_all doesn't support hooks with references as params
        foreach (module_implements('eventbrite_request_alter') as $module) {
          $function = $module . '_eventbrite_request_alter';
          $function($this);
        }
        break;
    }

    if (isset($this->params['id'])) {
      $id = $this->params['id'];
    }
    else {
      $id = isset($this->params['email']) ? $this->params['email'] : '';
    }

    // Build the querystring from the params
    $param_list = array();
    $this->params['user_key'] = $this->userKey;
    $this->params['app_key'] = $this->appKey;
    foreach ($this->params as $key => $value) {
      $param_list[] = $key . '=' . urlencode($value);
    }
    $this->query_string = join('&', $param_list);

    // Check cache, if there is something there and it is recent enough then use it
    // Otherwise make a call to the Eventbrite server
    if ($this->op_type == 'get' && $this->allowed_cache) {
      if (!$this->forceNoCache && $cache = cache_get('eventBriteCommon' . $this->op . '_' . $id . '_' .$this->query_string, 'cache_eventbrite')) {
        if (variable_get('eventbrite_debug', 0)) {
          drupal_set_message(
            t('From cache. Op: !op. Query String: !query',
            array('!op' => $this->op, '!query' => $this->query_string))
          );
        }
        $return = new stdClass();
        $return->object = simplexml_load_string($cache->data);
        $return->source = 'cache';
        return $return;
      }
    }

    if (variable_get('eventbrite_debug', 0)) {
      drupal_set_message(
        t($this->server. '!op?!query',
        array('!op' => $this->op, '!query' => $this->query_string))
      );
    }

    // Send HTTP request to the server - since we don't have fresh data
    if ($result = drupal_http_request($this->server . $this->op . '?' . $this->query_string) ) {
      // Process the result if there was one, and return simplexml_load_string($result->data)
      if ($return = $this->processResult($result)) {
        // If error type is set, log to watchdog
        if (isset($return->error_message)) {
          $watchdog_message = t('Error type: !error_type', array('!error_type' => $return->error_type)) . "\n";
          $watchdog_message .= t('Error msg: !error_message', array('!error_message' => $return->error_message)) . "\n";
          $watchdog_message .= t('Request: !request', array('!request' => $result->request)) . "\n";
          watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_WARNING);
          drupal_set_message(t(
            'EventBrite is unable to process your request.' . "\n" . 'Error Type: !errortype.' . "\n" . 'Error Messsage !error.' . "\n" . '' . "\n" . 'See the error log for more details or contact your administrator.',
            array('!error_type' => $return->error_type, '!error_message' => $return->error_message)
            ), 'error');
          return FALSE;
        }

        if ($this->op_type == 'get') {
          // store the returned string in the cache
          cache_set('eventBriteCommon' . $this->op . '_' . $id . '_' .$this->query_string, $return, 'cache_eventbrite', time() + $this->allowed_cache);
        }
        $xmlobj = new stdClass();
        $xmlobj->object = simplexml_load_string($return);
        $xmlobj->source = 'server';
        return $xmlobj;
      }
    }
  }

  /**
   * Function checkCache
   *
   * Check the cache for previous responses from Eventbrite server
   *
   * @param  [type] $request [description]
   * @return [type]          [description]
   */
  public function checkCache($request) {
    $result = db_select('eventbrite_cache', 'ec')
      ->fields('ec', array('op', 'id', 'query_string', 'timestamp', 'result'))
      ->condition('op', $this->op)
      ->condition('id', $this->param['id'])
      ->condition('query_string', $this->query_string);

    if ($result) {
      foreach ($result AS $row) {
        return $row;
      }
    }
  }

  private function processResult($result) {
    // Check HTTP return code
    if ($result->code) {
      switch ($result->code) {
        // Valid HTTP Request
        case 200:
          return $result->data;

        default:
          $result->success = FALSE;
          $watchdog_message = t('Error code: !code', array('!code' => $result->code)) . "\n";
          $watchdog_message .= t('Error msg: !error', array('!error' => $result->error)) . "\n";
          $watchdog_message .= t('Request: !request', array('!request' => $result->request)) . "\n";
          watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_WARNING);
          drupal_set_message(t(
            'The Eventbrite server can not be reached at this time. See the error log for more details or contact your administrator.'), 'error');
          // Bad web connection
          $watchdog_message = t('Error code: !code', array('!code' => $result->code)) . "\n";
          $watchdog_message .= t('Error msg: !error', array('!error' => $result->error)) . "\n";
          $watchdog_message .= t('Request: !request', array('!request' => $result->request)) . "\n";
          watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_ERROR);

          // TODO: Set this via drupal_set_message, ideally we could get rid of eventbrite_errors()
          drupal_set_message(t('The Eventbrite server can not be reached at this time.  Please contact the system administrator'), 'error');

          return FALSE;
      }
    }
  }

  public function get_op() {
    return $this->op;
  }

  public function set_op($inop) {
    $this->op = $inop;
  }

  public function get_op_type() {
    return $this->op_type;
  }

  public function set_op_type($inop_type) {
    $this->op_type = $inop_type;
  }

  public function get_query_string() {
    return $this->query_string;
  }

  public function set_query_string($inquery_string) {
    $this->query_string = $inquery_string;
  }

  public function get_server() {
    return $this->server;
  }

  public function set_server($inserver) {
    $this->server = $inserver;
  }

}
