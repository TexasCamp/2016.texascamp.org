<!-- footer -->
<footer id="footer" <?php print drupal_attributes($footer_attr); ?>>
  <?php if (!empty($page['footer'])): ?>
    <div class="footer">
      <div class="container">
        <div class="footer-inner">
          <div class="row">
            <?php print render($page['footer']); ?>
          </div>
        </div>
      </div>
    </div>
  <?php endif; ?>
  <?php if (!empty($page['footer_bottom'])): ?>
    <div class="subfooter">
      <div class="container">
        <div class="subfooter-inner">
          <div class="row">
            <?php print render($page['footer_bottom']); ?>
          </div>
        </div>
      </div>
    </div>
  <?php endif; ?>
</footer>