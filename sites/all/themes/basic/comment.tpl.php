<div class="comment <?php print $classes .' '. $zebra; if ($unpublished) { print 'unpublished'; } ?> clear-block">
  <div class="comment-inner">

    <?php if ($title): ?>
      <h4 class="title"><?php print $title ?></h4>
    <?php endif; ?>

    <?php if ($new) : ?>
      <span class="new"><strong><?php print drupal_ucfirst($new) ?></strong></span>
    <?php endif; ?>

    <?php print $picture; ?>

    <div class="submitted">
      <strong><?php print $submitted; ?></strong>
    </div>

    <div class="content">
      <?php print $content ?>
      <?php if ($signature): ?>
        <div class="user-signature clear-block">
          <?php print $signature; ?>
        </div>
      <?php endif; ?>
    </div>

    <?php if ($links): ?>
      <div class="links">
        <?php print $links; ?>
      </div>
    <?php endif; ?>  

  </div> <!-- /comment-inner -->
</div> <!-- /comment -->