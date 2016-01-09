<?php
//hide
hide($form['subject']);
hide($form['author']);
hide($form['comment_body']);

//unset
unset($form['author']['name']['#theme_wrappers']);
unset($form['author']['mail']['#theme_wrappers']);
unset($form['author']['homepage']['#theme_wrappers']);
unset($form['comment_body']['und'][0]['value']['#theme_wrappers']);

//textarea
$form['comment_body']['und'][0]['value']['#resizable'] = FALSE;
//submit
$form['actions']['submit']['#value'] = t('Post Comment');
$form['actions']['submit']['#attributes'] = array('class' => array('theme_btn'));
?>
<?php if (isset($form['author']['_author'])) : ?>
  <?php unset($form['author']['_author']['#theme_wrappers']); ?>
  <p><?php print drupal_render($form['author']['_author']); ?></p>
<?php else : ?>
  <p class="comment-form-author">
    <label><?php print $form['author']['name']['#title']; ?></label>
    <?php print drupal_render($form['author']['name']); ?>
  </p>
  <p class="comment-form-email">
    <label><?php print $form['author']['mail']['#title']; ?></label>
    <?php print drupal_render($form['author']['mail']); ?>
  </p>
  <p class="comment-form-url">
    <label><?php print $form['author']['homepage']['#title']; ?></label>
    <?php print drupal_render($form['author']['homepage']); ?>
  </p>
<?php endif; ?>
<p class="comment-form-comment">
  <label for="comment"><?php print $form['comment_body']['und'][0]['#title']; ?></label>
  <?php print drupal_render($form['comment_body']['und'][0]['value']); ?>
</p>
<p class="form-submit">
  <?php print drupal_render($form['actions']['submit']); ?>
</p>
<?php print drupal_render_children($form); ?>