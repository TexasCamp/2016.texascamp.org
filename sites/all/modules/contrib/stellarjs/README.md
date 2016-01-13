About
=====
Integrates the Stellar library into Bean parallax blocks.

Current Options
---------------
Allows you to use FlexSlider in a few different ways

- As a library to be used with any other theme or module by calling flexslider_add() (N.B. You may also use libraries_load('flexslider') or drupal_add_library('flexslider', 'flexslider'), but only if you want to control everything manually).
- Integrates with Fields (flexslider_fields)
- Adds a Views display mode (flexslider_views)

About Stellarjs
----------------

Library available at https://github.com/markdalgleish/stellar.js

**Parallax has never been easier.**
Add some simple data attributes to your markup, run $.stellar().
That's all you need to get started. Scroll right to see Stellar.js in action.

**Precisely align elements and backgrounds.**
All elements and backgrounds will return to their original position when they meet the edge of the screen—plus or minus your own optional offset.


Installation
============

Dependencies
------------

- [Libraries API 2.x](http://drupal.org/project/libraries)
- [Stellar Library](http://markdalgleish.com/projects/stellar.js)

Tasks
-----

1. Download the Stellarjs library from https://github.com/markdalgleish/stellar.js
2. Unzip the file and rename the folder to "stellarjs" (pay attention to the case of the letters)
3. Put the folder in a libraries directory
    - Ex: sites/all/libraries
4. The following files are required (last file is required for javascript debugging)
    - jquery.stellar.min.js
    - jquery.stellar.js
5. Ensure you have a valid path similar to this one for all files
    - Ex: sites/all/libraries/stellar/jquery.stellar.min.js

That's it!


External Links
==============

- [Wiki Documentation for Stellarjs](https://github.com/markdalgleish/stellar.js/blob/master/README.md)