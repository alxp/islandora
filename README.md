# Islandora [![Build Status](https://travis-ci.org/Islandora/islandora.png?branch=7.x)](https://travis-ci.org/Islandora/islandora)

## Introduction

This module includes the core functionality for interacting with Fedora Repository objects through the Drupal interface.

For installation and customization instructions please see the [documentation and the DuraSpace Wiki](https://wiki.duraspace.org/display/ISLANDORA/Islandora).

All bugs, feature requests and improvement suggestions are tracked at the [DuraSpace JIRA](https://jira.duraspace.org/browse/ISLANDORA).


## Requirements

This module requires the following modules/libraries:

* [Tuque](https://github.com/islandora/tuque)

Tuque is expected to be in one of two paths:

* sites/all/libraries/tuque (libraries directory may need to be created)
* islandora_folder/libraries/tuque

More detailed requirements are outlined in the [Installing the Islandora Essential Modules](https://wiki.duraspace.org/display/ISLANDORA/milestone+5+-++Installing+the+Islandora+Essential+Modules) chapter of the documentation.

### Optional Requirements

If you want to support languages other than English, download and enable [String Translation](https://drupal.org/project/i18n), and follow our [guide](https://github.com/Islandora/islandora/wiki/Multilingual-Support) for setting up additional languages.

## Installation

This is one Drupal module in a suite of modules (and stack of related software) which are required for Islandora to function correctly. For full installation instructions please see the [documentation in the DuraSpace Wiki](https://wiki.duraspace.org/display/ISLANDORA/Islandora).

### Global Fedora XACML policies
Before installing Islandora, the XACML policies located [here](https://github.com/Islandora/islandora-xacml-policies) should be copied into the Fedora global XACML policies folder. This will allow "authenticated users" in Drupal to access Fedora API-M functions (create, edit, and delete objects in Fedora).

Notes:
* Delete the `permit-upload-to-anonymous-user.xml` and `permit-apim-to-anonymous-user.xml` policies unless you want to allow anonymous (unauthenticated) users to create Islandora objects (not recommended).
* Delete the `deny-purge-datastream-if-active-or-inactive.xml` to allow users to purge (permanently remove) datastream versions.

More detailed information can be found in the 'Set XACML Policies' in the [Installing Fedora](https://wiki.duraspace.org/display/ISLANDORA/milestone+1+-+Installing+Fedora) chapter of the documentation.

### Protecting the 'anonymous' username
The `islandora_drupal_filter` passes the username of 'anonymous' through to Fedora for unauthenticated Drupal Users. A user with the name of 'anonymous' may have XACML policies applied to them that are meant to be applied to Drupal users that are not logged in or vice-versa. This is a potential security issue that can be plugged by creating a user named 'anonymous' and restricting access to the account. If this is done after installing Islandora, Drupal's cron can be run to remove expired authentication tokens.


## Configuration

Configuration that applies to all solution packs, including the location of the Fedora Repository, the namespaces accessible by this instance of Islandora, and whether to generate derivatives on ingest, are available at  `admin/islandora/configure`.

![Configuration](https://user-images.githubusercontent.com/1943338/40320855-724afcba-5d03-11e8-9109-0b8413349839.png)

### Breadcrumb Generation

Whether Drupal breadcrumbs (showing an object's parent hierarchy) should be displayed, and how they are generated, can be set on the configuration page. Other modules (such as [Islandora Solr](https://github.com/Islandora/islandora_solr_search)) may provide  alternatives that perform better at large scales than the built-in Resource Index query.

### Inactive and Deleted Objects

By default, objects with the [Fedora state](https://wiki.duraspace.org/display/FEDORA38/Fedora+Digital+Object+Model) of "Inactive" or "Deleted" are accessible to all users with the Drupal permission "View repository objects". It is possible to use a separate permission to control access to these non-"Active" objects, but this permission must first be enabled at `admin/islandora/configure`, then the permssion can be granted to desired roles at `admin/people/permissions`.

### Customization

* Hooks provided by Islandora are documented in `islandora.api.php`. 
* A [detailed tutorial](https://github.com/Islandora/islandora/wiki/Multi-paged-Ingest-Forms) on extending the multi-page ingest forms is available on the Github (developers') Wiki.


## Documentation

Further documentation for this module is available at [our documentation wiki](https://wiki.duraspace.org/display/ISLANDORA/Islandora+Core+Module).

## Troubleshooting/Issues

NOTE: There has been a function signature change for the `ingestDatastream` function within Tuque which will be deprecated after the 7.x-1.10 release. To read about it in detail please see the [JIRA ticket](https://jira.duraspace.org/browse/ISLANDORA-1995). For the time being there is a warning stating that this will become deprecated and that code that utilizes this specific behavior should be updated. Once this code is updated the `islandora_deprecation_return_false_when_datastream_exists` variable may be set to FALSE so the warning no longer displays. An example for doing this with drush: `drush vset islandora_deprecation_return_false_when_datastream_exists FALSE`.

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

## Maintainers/Sponsors

Current maintainers:

* [Diego Pino](https://github.com/DiegoPino)
* [Jonathan Green](https://github.com/jonathangreen)

## Development

If you would like to contribute to this module, please check out [CONTRIBUTING.md](CONTRIBUTING.md). In addition, we have helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the [Islandora.ca](http://islandora.ca) site.

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
