#!/bin/bash

# Common checks to get run during the 'script' section in Travis.

# Lint
find $TRAVIS_BUILD_DIR -type f \( -name '*.php' -o -name '*.inc' -o -name '*.module' -o -name '*.install' -o -name '*.test' \) -exec php -l {} \;

# Check line endings
$ISLANDORA_DIR/tests/scripts/line_endings.sh $TRAVIS_BUILD_DIR

# Coding standards
drush coder-review --reviews=production,security,style,i18n,potx,sniffer $TRAVIS_BUILD_DIR

# Copy/paste detection
phpcpd --names *.module,*.inc,*.test $TRAVIS_BUILD_DIR
