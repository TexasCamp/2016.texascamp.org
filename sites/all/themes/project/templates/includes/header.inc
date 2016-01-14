<!-- Header -->
<header <?php print drupal_attributes($header_attr); ?> >
    <div class="container">
      <div class="row">

          <div class="col-md-3">
            <!-- header-left start -->
            <div class="header-left clearfix">
              <!-- logo -->
              <?php if ($logo): ?>
                <div id="logo" class="logo">
                  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
                    <img class="img-responsive" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                  </a>
                </div>
              <?php endif; ?>
              <!-- name-and-slogan -->
              <?php if (!empty($site_name)): ?>
                <div class="site-name">
                  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
                </div>
              <?php endif; ?>
              <?php if (!empty($site_slogan)): ?>
                <div class="site-slogan">
                  <?php print $site_slogan; ?>
                </div>
              <?php endif; ?>
            </div> <!-- header-left start -->
          </div>

          <div class="col-md-9">
            <!-- header-right start -->
            <div class="header-right clearfix">
              <!-- main-navigation start -->
              <div <?php if ($navbar_attr){ print drupal_attributes($navbar_attr); } ?>>
                <nav class="navbar navbar-default" role="navigation">
                  <div class="container-fluid">
                    <!-- Toggle get grouped for better mobile display -->
                    <div class="navbar-header">
                      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar-collapse-1">
                        <span class="sr-only">Toggle navigation</span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                      </button>
                    </div>
                    <!-- Collect the nav links, forms, and other content for toggling -->
                    <div class="collapse navbar-collapse" id="navbar-collapse-1">
                      <?php if (!empty($primary_nav)): ?>
                        <?php print render($primary_nav); ?>
                      <?php endif; ?>
                      <!-- header buttons -->
                      <div class="header-dropdown-buttons hidden-xs">
                        <?php if($toggle_search): ?>
                          <div class="btn-group dropdown">
                            <button type="button" class="btn dropdown-toggle" data-toggle="dropdown" aria-expanded="false">
                              <?php print $search_icon; ?>
                            </button>
                            <ul class="dropdown-menu dropdown-menu-right dropdown-animation">
                              <li><?php print $search_box; ?></li>
                            </ul>
                          </div>
                        <?php endif; ?>
                      </div> <!-- header buttons end-->
                    </div> <!-- end-navbar -->
                  </div>
                </nav>
              </div>
            </div>
          </div>
      </div> <!-- /.row -->
    </div> <!-- /.container -->
</header>
