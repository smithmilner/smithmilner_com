<div class="node blog-entry <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
	<div class="node-inner">
		<?php if (!$page): ?>
			<h3 class="title blog-title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
		<?php endif; ?>

		<?php print $picture; ?>

		<?php if ($submitted): ?>
			<span class="submitted"><strong><?php print $submitted; ?></strong></span>
		<?php endif; ?>

		<div class="content">
			<?php print $content; ?>
		</div>
		
		<div class="blog-footer">
			<?php if ($links): ?> 
		      <div class="links"><?php print $links; ?></div>
			<?php endif; ?>

			<?php if ($terms): ?>
		      <div class="taxonomy"><?php print $terms; ?></div>
		    <?php endif;?>
		</div><!-- / "portfolio-footer" -->

	</div> <!-- /node-inner -->
</div> <!-- /node-->