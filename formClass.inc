<?php

// $Id$

/*
 * Created on Jan 22, 2008
 */

class formClass {

  function formClass() {
    module_load_include('inc', 'formClass', '');
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
  }

  /*
   * create the paths for urls and map them to php functions
   */

  function createMenu() {
    $items = array();

    $items['admin/settings/fedora_repository'] = array(
      'title' => t('Fedora collection list'),
      'description' => t('Enter the Fedora Collection information here'),
      'page callback' => 'drupal_get_form',
      'page arguments' => array('fedora_repository_admin'),
      'access arguments' => array('administer site configuration'),
      'type' => MENU_NORMAL_ITEM,
    );
    $items['admin/settings/fedora_repository/collection'] = array(
      'title' => t('Collection list'),
      'description' => t('Enter the Fedora collection information here.'),
      'access arguments' => array('administer site configuration'),
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => 0,
    );

    $items['admin/settings/fedora_repository/demoobjects'] = array(
        'title' => t('Solution Packs'),
        'description' => t('Install content models and collections required by installed solution packs.'),
        'page callback' => 'fedora_repository_solution_packs_page',
        'access arguments' => array('add fedora datastreams'),
        'file' => 'fedora_repository.solutionpacks.inc',
        'type' => MENU_LOCAL_TASK,
    );

    $items['islandoracm.xsd'] = array(
      'title' => t('Islandoracm XML Schema Definition'),
      'page callback' => 'fedora_repository_display_schema',
      'page arguments' => array('islandoracm.xsd'),
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection'),
    );

    $items['collection_policy.xsd'] = array(
      'title' => t('Islandoracm XML Schema Definition'),
      'page callback' => 'fedora_repository_display_schema',
      'page arguments' => array('collection_policy.xsd'),
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection'),
    );

    $items['fedora'] = array(
      'page callback' => 'repository_page',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection'),
    );
    $repository_title = variable_get('fedora_repository_title', 'Digital repository');
    if (trim($repository_title) != '') {
      $respository_title = t($repository_title);
    }
    else {
      $repository_title = NULL;
    }
    $items['fedora/repository'] = array(
      'title' => $repository_title,
      'page callback' => 'repository_page',
      'type' => MENU_NORMAL_ITEM,
      'access arguments' => array('view fedora collection'),
        // 'access' => TRUE
    );

    $items['fedora/repository/service'] = array(
      'page callback' => 'repository_service',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection'),
    );

    $items['fedora/repository/object_download'] = array(
      'title' => t('Download object'),
      'page callback' => 'fedora_object_as_attachment',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection')
    );
    $items['fedora/repository/editmetadata'] = array(
      'title' => t('Edit metadata'),
      'page callback' => 'fedora_repository_edit_qdc_page',
      // 'page arguments' => array(1),
      //'type' =>  MENU_LOCAL_TASK,
      'type' => MENU_CALLBACK,
      'access arguments' => array('edit fedora meta data')
    );
    $items['fedora/repository/purgeStream'] = array(
      'title' => t('Purge data stream'),
      'page callback' => 'fedora_repository_purge_stream',
      'type' => MENU_CALLBACK,
      'access arguments' => array('purge objects and datastreams')
    );
    $items['fedora/repository/replaceStream'] = array(
      'title' => t('Replace Stream'),
      'page callback' => 'fedora_repository_replace_stream',
//       'callback arguments' => array(3, 4),
      'type' => MENU_CALLBACK,
//       'access callback' => 'fedora_repository_user_access',
      'access arguments' => array('add fedora datastreams'),
    );
    $items['fedora/repository/purgeObject'] = array(
      'title' => t('Purge object'),
      'page callback' => 'fedora_repository_purge_object',
      // 'type' =>  MENU_LOCAL_TASK,
      'type' => MENU_CALLBACK,
      'access arguments' => array('purge objects and datastreams')
    );
    $items['fedora/repository/addStream'] = array(
      'title' => t('Add stream'),
      'page callback' => 'add_stream',
      // 'type' => MENU_LOCAL_TASK,
      'type' => MENU_CALLBACK,
      'access arguments' => array('add fedora datastreams')
    );

    $items['fedora/repository/collection'] = array(
      'title' => t('Collection view'),
      'page callback' => 'fedora_collection_view',
      'type' => MENU_CALLBACK,
      'access argruments' => array('view fedora collection')
    );
    //new for mnpl******************************************
    $items['fedora/repository/mnpl_advanced_search'] = array(
      'title' => t('Repository advanced search'),
      'page callback' => 'fedora_repository_mnpl_advanced_search',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection')
    );
    $items['fedora/ingestObject'] = array(
      'title' => t('Ingest object'),
      'page callback' => 'fedora_repository_ingest_object',
      'type' => MENU_CALLBACK,
      'access arguments' => array('add fedora datastreams')
    );

    $items['fedora/repository/list_terms'] = array(
      'title' => t('List terms'),
      'page callback' => 'fedora_repository_list_terms',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection')
    );

    $items['fedora/tagging/add_tag/js'] = array(
      'page callback' => 'fedora_tagging_add_tag_js',
      'access arguments' => array('edit tags datastream'),
      'type' => MENU_CALLBACK,
    );


    /* Export functionality */
    $items['fedora/basket'] = array(
      'title' => t('Fedora Basket'),
      'description' => t('View and download objects added to your basket'),
      'page callback' => 'fedora_repository_basket',
      'access arguments' => array('view fedora collection'),
      'type' => MENU_CALLBACK,
    );

    $items['fedora/repository/addToBasket'] = array(
      'page callback' => 'fedora_repository_add_to_basket',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection'),
    );

    $items['fedora/repository/removeFromBasket'] = array(
      'page callback' => 'fedora_repository_remove_from_basket',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection'),
    );

    $items['fedora/repository/add_search_results_to_basket'] = array(
      'page callback' => 'fedora_repository_add_search_results_to_basket',
      'type' => MENU_CALLBACK,
      'access arguments' => array('view fedora collection'),
    );

    return $items;
  }

  function createAdminForm() {
    if (!user_access('administer site configuration')) {
      drupal_set_message(t('You must be a site administrator to edit the Fedora collecitons list.'), 'error');
      return;
    }
    module_load_include('inc', 'fedora_repository', 'api/fedora_utils');
    module_load_include('inc', 'fedora_repository', 'ObjectHelper');
    $form = array();
    $form['fedora_repository_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Default collection name'),
      '#default_value' => variable_get('fedora_repository_name', 'Islandora demos collection'),
      '#description' => t('The Name of the collection to grab the list of items from'),
      '#required' => TRUE,
      '#weight' => -2
    );
    $form['fedora_repository_pid'] = array(
      '#type' => 'textfield',
      '#title' => t('Default collection PID'),
      '#default_value' => variable_get('fedora_repository_pid', 'islandora:top'),
      '#description' => t('The PID of the collection object to grab the list of items from'),
      '#required' => TRUE,
      '#weight' => -2
    );

    $form['fedora_collection_model_pid'] = array(
      '#type' => 'textfield',
      '#title' => t('Default Collection Model PID'),
      '#default_value' => variable_get('fedora_collection_model_pid', 'islandora:collectionCModel'),
      '#description' => t('The PID of the default Collection Model Object'),
      '#required' => TRUE,
      '#weight' => -2
    );

    $form['fedora_content_model_collection_pid'] = array(
      '#type' => 'textfield',
      '#title' => t('Default Content Model Collection PID'),
      '#default_value' => variable_get('fedora_content_model_collection_pid', 'islandora:ContentModelCollection'),
      '#description' => t('The PID of the Content Model Collection Object'),
      '#required' => TRUE,
      '#weight' => -2
    );


    $form['fedora_repository_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora RISearch URL'),
      '#default_value' => variable_get('fedora_repository_url',
          'http://localhost:8080/fedora/risearch'),
      '#description' => t('The url of the Fedora server'), '#required' => TRUE,
      '#weight' => 0
    );
    $form['fedora_fgsearch_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora Lucene search URL'),
      '#default_value' => variable_get('fedora_fgsearch_url', 'http://localhost:8080/fedoragsearch/rest'),
      '#description' => t('The url of the Lucene Fedora server'),
      '#required' => TRUE,
      '#weight' => 0
    );
    $form['fedora_index_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora Lucene index name'),
      '#default_value' => variable_get('fedora_index_name', 'BasicIndex'),
      '#description' => t('The name of the Lucene index to search'),
      '#required' => TRUE,
      '#weight' => 0
    );
    $form['fedora_soap_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora SOAP Url'),
      '#default_value' => variable_get('fedora_soap_url', 'http://localhost:8080/fedora/services/access?wsdl'),
      '#description' => t('The URL to use for SOAP connections'),
      '#required' => TRUE,
      '#weight' => 0,
      '#suffix' => '<p>' . (fedora_available() ? '<img src="' . url('misc/watchdog-ok.png') . '"/>' . t('Successfully connected to Fedora server at !fedora_soap_url', array('!fedora_soap_url' => variable_get('fedora_soap_url', ''))) : '<img src="' . url('misc/watchdog-error.png') . '"/> ' . t('Unable to connect to Fedora server at !fedora_soap_url</p>', array('!fedora_soap_url' => variable_get('fedora_soap_url', '')))),
    );
    $form['fedora_base_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora base URL'),
      '#default_value' => variable_get('fedora_base_url', 'http://localhost:8080/fedora'),
      '#description' => t('The URL to use for REST-type connections'),
      '#required' => TRUE,
      '#weight' => 0,
    );

    $form['fedora_soap_manage_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora SOAP management URL'),
      '#default_value' => variable_get('fedora_soap_manage_url', 'http://localhost:8080/fedora/services/management?wsdl'), '#description' => t('The URL to use for SOAP API-M connections'),
      '#required' => TRUE,
      '#weight' => 0
    );

    $form['fedora_solr_search_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora Solr search URL'),
      '#default_value' => variable_get('fedora_solr_search_url', 'http://localhost:8080/solr'), '#description' => t('The URL to use for Solr searching'),
      '#required' => TRUE,
      '#weight' => 0
    );

// will allow admin user to remove namepsace restrictions if not explicitly disallowed  in settings.php
    if (variable_get('allow_open_namespace', TRUE)) {
      $form['fedora_namespace'] = array(
        '#type' => 'fieldset',
      );

      $form['fedora_namespace']['fedora_namespace_restriction_enforced'] = array(
        '#weight' => -1,
        '#type' => 'radios',
        '#title' => t('Enforce namespace restrictions'),
        '#options' => array(
          TRUE => t('Enabled'),
          FALSE => t('Disabled')
        ),
        '#description' => t('Allow administrator to restrict user\'s access to the PID namepaces listed below'),
        '#default_value' => variable_get('fedora_namespace_restriction_enforced', TRUE)
      );

      $form['fedora_namespace']['fedora_pids_allowed'] = array(
        '#type' => 'textfield',
        '#title' => t('PID namespaces allowed in this Drupal install'),
        '#default_value' => variable_get('fedora_pids_allowed', 'default: demo: changeme: islandora: ilives: '),
        '#description' => t('A space separated list PID namespaces that users are permitted to access from this Drupal installation. <br /> This could be more than a simple namespace ie demo:mydemos.'),
        '#weight' => 0
      );
    }
    else {
      $form['fedora_pids_allowed'] = array(
        '#type' => 'textfield',
        '#title' => t('PID namespaces allowed in this Drupal install'),
        '#default_value' => variable_get('fedora_pids_allowed', 'default: demo: changeme: islandora: ilives: '),
        '#description' => t('A space separated list PID namespaces that users are permitted to access from this Drupal installation. <br /> This could be more than a simple namespace ie demo:mydemos.'),
        '#weight' => 0
      );
    }
    $form['fedora_repository_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Fedora Repository Title'),
      '#default_value' => variable_get('fedora_repository_title', 'Digital Repository'),
      '#description' => t('The title displayed when viewing collections and objects in  /fedora/repository. Leave blank to display no title. Note that the menus must be rebuilt after changing this variable.'),
    );

    $form['fedora_object_display_title'] = array(
      '#type' => 'select',
      '#title' => t('Display Object Title Behaviour'),
      '#default_value' => variable_get('fedora_object_display_title', ObjectHelper::$DISPLAY_ALWAYS),
      '#options' => array(ObjectHelper::$DISPLAY_ALWAYS => t('Always'), ObjectHelper::$DISPLAY_NEVER => t('Never'), ObjectHelper::$DISPLAY_NO_MODEL_OUTPUT => t('Only if no Content Model display output.')),
      '#description' => t('Determines when to display the object (or collection) title when viewing an object/collection page.'),
    );

    $form['fedora_object_display_description'] = array(
      '#type' => 'select',
      '#title' => t('Display Object Description Behaviour'),
      '#default_value' => variable_get('fedora_object_display_description', ObjectHelper::$DISPLAY_ALWAYS),
      '#options' => array(ObjectHelper::$DISPLAY_ALWAYS => t('Always'), ObjectHelper::$DISPLAY_NEVER => t('Never'), ObjectHelper::$DISPLAY_NO_MODEL_OUTPUT => t('Only if no Content Model display output.')),
      '#description' => t('Determines when to display the default object (or collection) description fieldset when viewing an object/collection page.'),
    );

    $form['fedora_object_restrict_datastreams'] = array(
      '#type' => 'checkbox',
      '#title' => t('Restrict Access to Fedora Object Datastreams'),
      '#default_value' => variable_get('fedora_object_restrict_datastreams', FALSE),
      '#description' => t('When enabled, restricts access to fedora object datastreams that are not listed in the Islandora Content Model for the object (unless the user is an administrator).'),
    );

    $form['fedora_collection_display_list'] = array(
      '#type' => 'select',
      '#title' => t('Display Collection List Behaviour'),
      '#default_value' => variable_get('fedora_collection_display_list', ObjectHelper::$DISPLAY_ALWAYS),
      '#options' => array(ObjectHelper::$DISPLAY_ALWAYS => t('Always'), ObjectHelper::$DISPLAY_NEVER => t('Never'), ObjectHelper::$DISPLAY_NO_MODEL_OUTPUT => t('Only if no Content Model display output.')),
      '#description' => t('Determines when to display the list of objects when viewing a collection page.'),
    );

    //Export functionality
    $form['module']['export_area'] = array(
      '#type' => 'textfield',
      '#title' => t('Export area'),
      '#default_value' => variable_get('export_area', file_directory_path() . '/fedora_export_area'),
      '#description' => t("Path to the export area. It must be accessible by druapl (i.e. apache user)."),
      '#required' => TRUE,
    );

    $form['#attributes'] = array('enctype' => "multipart/form-data");

    // Additional form handling for file uploads.
    $form['#submit'][] = 'fedora_repository_admin_settings_submit';
    return system_settings_form($form);
  }

  function updateMetaData($form_id, $form_values, $client) {
    // ======================================
    // = begin creation of foxml dom object =
    // ======================================
    $dom = new DomDocument("1.0", "UTF-8");
    $dom->formatOutput = TRUE;

    ///begin writing qdc

    $oai = $dom->createElement("oai_dc:dc");
    $oai->setAttribute('xmlns:oai_dc', "http://www.openarchives.org/OAI/2.0/oai_dc/");
    $oai->setAttribute('xmlns:dc', "http://purl.org/dc/elements/1.1/");
    $oai->setAttribute('xmlns:dcterms', "http://purl.org/dc/terms/");
    $oai->setAttribute('xmlns:xsi', "http://www.w3.org/2001/XMLSchema-instance");

    // DC elements
    $previousElement = NULL; // Used in case we have to nest elements for qualified dublin core.
    foreach ($form_values as $key => $value) {
      $index = strrpos($key, '-');
      $key = substr($key, 0, $index);
      $test = substr($key, 0, 2);
      if ($test == 'dc' || $test == 'ap') { // Don't try to process other form values.
        try {
          if (!strcmp(substr($key, 0, 4), 'app_')) {
            $key = substr($key, 4);
            $previousElement->appendChild($dom->createElement($key, $value));
          }
          else {
            $previousElement = $dom->createElement($key, $value);
            $oai->appendChild($previousElement);
          }
        } catch (exception $e) {
          drupal_set_message(t($e->getMessage()), 'error');
          continue;
        }
      }
    }

    $dom->appendChild($oai);

    if (!$client) {
      return;
    }

    $pid = $form_values['pid'];
    $dsId = $form_values['dsid'];
    $params = array(
      "pid" => $pid,
      "dsID" => $dsId,
      "altIDs" => "",
      "dsLabel" => "Qualified Dublin Core",
      "MIMEType" => "text/xml",
      "formatURI" => "URL",
      "dsContent" => $dom->saveXML(), "checksumType" => "DISABLED", "checksum" => "none",
      "logMessage" => "datastream_modified", "force" => "TRUE");
    try {
      $object = $client->__soapCall('ModifyDatastreamByValue', array($params));
    } catch (exception $e) {
      drupal_set_message(t("Error updating metadata ") . $e->getMessage(), 'error');
    }
  }

  // queries the collection object for a childsecurity datastream and if found parses it
  // to determine if this user is allowed to ingest in this collection
  // we assume if they are able to modify objects in the collection they can ingest as well.
  function can_ingest_here($collection_pid) {
    module_load_include('inc', 'fedora_repository', 'SecurityClass');
    $securityClass = new SecurityClass();
    return $securityClass->canIngestHere($collection_pid);
  }

  /**
   * Create a multi step form (wizard) for ingesting objects into Fedora
   */
  function createIngestForm($collection_pid, $collection_label, &$form_state) {
    global $user;
    module_load_include('inc', 'fedora_repository', 'CollectionPolicy');
    // drupal_add_js("function _imce_ingest_ImceFinish(path, w, h, s, imceWin) {imceWin.close(); document.getElementById('edit-ingest-file-location').value = path;}",'inline','header');

    if (!user_access('ingest new fedora objects')) {
      drupal_set_message(t('You do not have permission to ingest.'), 'error');
      return '';
    }
    if (empty($form_state['storage']['step'])) {
      // we are coming in without a step, so default to step 1
      $form_state['storage']['step'] = 1;
    }
    //this uses drupal's permissions at this point no xacml yet. xacml decisions are made by fedora
    if (!$this->can_ingest_here($collection_pid)) {
      drupal_set_message(t('You do not have premission to ingest here.'));
      return '';
    }

    if ($collection_pid == NULL) {
      drupal_set_message(t('You must specify an collection object pid to ingest an object.'), 'error');
      return FALSE;
    }
    if (($cp = CollectionPolicy::loadFromCollection($collection_pid)) === FALSE) {
      drupal_set_message(t('Unable to load collection policy \'' . $collection_pid . '\'.'));
      return FALSE;
    }


    $contentModels = $cp->getContentModels();

    if (!$contentModels) {
      drupal_set_message(t('No content models associated with this collection: !collection_label. Please contact your administrator.', array('!collection_label' => $collection_label)), 'error');
      return FALSE;
    }
    $modelsForForm = array();
    foreach ($contentModels as $contentModel) {
      $identifier = $contentModel->getIdentifier();
      $name = $contentModel->name;
      $modelsForForm["$identifier"] = "$name";
    }

    switch ($form_state['storage']['step']) {
      case 1:
        $form['indicator'] = array(
          '#type' => 'fieldset',
          '#title' => t('Ingest digital object into collection_pid !collection_label Step #1', array('collection_pid' => $collection_pid, '!collection_label' => $collection_label))
        );

        $form['indicator']['models'] = array(// content models available
          '#type' => 'select',
          '#title' => t('Content models available'),
          '#options' => $modelsForForm,
          //'#description' => t('Content models available in this collection.  A content model defines what is allowed in a collection and what to do with a file when it is uploaded (An example may creating a thumbnail from an image.).')
          '#description' => t('Content models define datastream composition, relationships between this and other content models, and the mandatory behaviors associated with each digital object.<br /> Additional information may be found <a href="https://wiki.duraspace.org/display/FEDORACREATE/Content+Models+Overview">here.</a> ')
        );
        break;

      case 2:
        module_load_include('inc', 'fedora_repository', 'MimeClass'); // Why this include? --Zac, 2010-09-17
        $contentModelPid = ContentModel::getPidFromIdentifier($form_state['values']['models']);
        $contentModelDsid = ContentModel::getDSIDFromIdentifier($form_state['values']['models']);

        if (($cm = ContentModel::loadFromModel($contentModelPid, $contentModelDsid)) !== FALSE) {
          $form = $cm->buildIngestForm($form, $form_state);
          if ($form === FALSE) {

            drupal_set_message(t("Error Building Ingest Form."), 'error');
            foreach (ContentModel::$errors as $err) {
              drupal_set_message($err, 'error');
            }
          }
        }

        break;
    }

    $form['collection_pid'] = array(
      '#type' => 'hidden',
      '#value' => $collection_pid
    );

    if ($form_state['storage']['step'] < 2) {
      $button_name = t('Next');
    }
    else {
      $prefix = t('Please be patient. Once you click next there may be a number of files created.  Depending on your content model this could take a few minutes to process.<br />');
      $button_name = t('Ingest');
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#submit' => array('fedora_repository_ingest_form_submit'),
      '#value' => $button_name
    );

    return $form;
  }

  // this function may not be being used
  function createAddDataStreamForm($pid, &$form_state) {
    //dump_vars($form_state);
    // Populate the list of datastream IDs.

    module_load_include('inc', 'fedora_repository', 'ObjectHelper');
    module_load_include('inc', 'fedora_repository', 'ContentModel');
    module_load_include('inc', 'fedora_repository', 'api/fedora_item');

    $obj_helper = new ObjectHelper();
    $content_models = $obj_helper->get_content_models_list($pid);
    $available_dsids = array();
    if (!empty($content_models)) {
      foreach ($content_models as $content_model) {


        $newElements = $content_model->listDatastreams();
        if (!empty($newElements)) {
          $available_dsids = array_merge($available_dsids, $newElements);
        }

      }
    }

    $item = new Fedora_Item($pid);
    $used_datastreams = $item->get_datastreams_list_as_SimpleXML();
    $used_datastream_ids = array();
    foreach ($used_datastreams->datastreamDef as $used_datastream) {
      array_push($used_datastream_ids, $used_datastream->ID);
    }
    $unused_dsids = array();

    if ($form_state['submitted'] && $form_state['clicked_button']['#value'] != 'OK') {
      $form['add_datastream_label'] = array(
        '#value' => t('<br /><h3>The datastream has been uploaded.</h3>'),
        '#weight' => -10,
      );
      $form['#redirect'] = "fedora/repository/$pid/";
      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('OK')
      );
      return $form;
    }
    if (!empty($available_dsids)) {
      $unused_dsids = array_diff($available_dsids, $used_datastream_ids);
      if (empty($unused_dsids)) {
        return;
      }
    }

    $form['add_datastream_label'] = array(
      '#value' => t('<br /><h3>Add Datastream:</h3>'),
      '#weight' => -10,
    );

    $form['pid'] = array(
      '#type' => 'hidden',
      '#value' => "$pid"
    );

    $form['stream_label'] = array(
      '#title' => 'Datastream Label',
      '#required' => 'TRUE',
      '#description' => t('A Human readable label'),
      '#type' => 'textfield'
    );

    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['add-stream-file-location'] = array(
      '#type' => 'file',
      '#title' => t('Upload Document'),
      '#size' => 48,
      // '#required'=>'TRUE',
      '#description' => t('The file to upload.')
    );
    $form['#redirect'] = "fedora/repository/$pid/";
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Add Datastream')
    );

    if (!empty($unused_dsids)) {
       $dsidsForForm = array();
        foreach ($unused_dsids as $dsid){
            $dsidsForForm[$dsid]=$dsid;
        }
      $form['stream_id'] = array(
        '#type' => 'select',
        '#title' => t('Datastream ID'),
        '#default_value' => variable_get('feed_item_length', 'teaser'),
        '#weight' => '-1',
        '#description' => t('Datastream IDs defined by the content model.'),
      ); 
      $form['stream_id']['#options'] = array_combine($unused_dsids, $unused_dsids);
    } 
    else {
      $form['stream_id'] = array(
        '#title' => 'Datastream ID',
        '#required' => 'TRUE',
        '#description' => t('An ID for this stream that is unique to this object. Must start with a letter and contain only alphanumeric characters and dashes and underscores.'),
        '#type' => 'textfield',
        '#weight' => -1,
      );
    }
    return $form;
  }

  /**
   * Creates a drupal form to edit either the QDC or DC datastream
   */
  function createMetaDataForm($pid, $dsId = NULL, $client) {
    if (!isset($dsId)) {
      $dsId = 'QDC';
    }

    //$client = getSoapClient(variable_get('fedora_soap_url', 'http://localhost:8080/fedora/services/access?wsdl'));
    $params = array('pid' => "$pid", 'dsID' => "$dsId", 'asOfDateTime' => "");
    try {
      $object = $client->__soapCAll('getDatastreamDissemination', array('parameters' => $params));
    } catch (Exception $e) {
      return array();
    }

    $content = $object->dissemination->stream;
    $content = trim($content);
    $doc = new DOMDocument();
    if (!$doc->loadXML($content)) {
      echo "error loading xml";
    }

    $oai_dc = $doc->getElementsByTagName('dc');

    $dcItems = $oai_dc->item(0)->getElementsByTagName('*');
    $form = array();
    for ($i = 0; $i < $dcItems->length; $i++) {
      $name = $dcItems->item($i)->nodeName;
      if ($name == 'dc:description') {
        $form["$name" . '-' . "$i"] = array(
          '#title' => $name,
          '#type' => 'textarea',
          '#default_value' => $dcItems->item($i)->nodeValue,
          '#description' => 'Dublin Core ' . substr($dcItems->item($i)->nodeName, 3)
        );
      }
      elseif ($name == 'dc:title') {
        $form["$name" . '-' . "$i"] = array(
          '#title' => $name,
          '#type' => 'textfield',
          '#required' => 'TRUE',
          '#default_value' => $dcItems->item($i)->nodeValue,
          '#description' => 'Dublin Core ' . substr($dcItems->item($i)->nodeName, 3)
        );
      }
      else {
        if ($oai_dc->item(0)->nodeName != $dcItems->item($i)->parentNode->nodeName) {
          $description = strstr($name, ':');
          $form['app_' . "$name" . '-' . "$i"] = array(
            '#title' => $name,
            '#type' => 'textfield',
            '#default_value' => $dcItems->item($i)->nodeValue,
            '#description' => 'Dublin Core ' . substr($description, 1)
          );
        }
        else {
          $field_type = 'textfield';
          $value = $dcItems->item($i)->nodeValue;
          if ($name == 'dc:coverage') {
            $value = '';
          }
          if ($name == 'dc:rights') {
            $field_type = 'textarea';
          }
          $description = strstr($name, ':');
          $form["$name" . '-' . "$i"] = array(
            '#title' => $name,
            '#type' => $field_type,
            '#default_value' => $value,
            '#description' => 'Dublin Core ' . substr($description, 1)
          );
        }
      }
    }

    $form['pid'] = array(
      '#type' => 'hidden',
      '#value' => "$pid"
    );
    $form['dsid'] = array(
      '#type' => 'hidden',
      '#value' => "$dsId"
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update Metadata'),
    );

    return $form;
  }

  /**
   * Creates a form for replacing datastream
   */
  function createReplaceDataStreamForm($pid, $dsId, $dsLabel, &$form_state) {
    $form = array();

    $form['#attributes']['enctype'] = 'multipart/form-data';
    $form['file'] = array(
      '#type' => 'file',
      '#title' => t('Upload Document'),
      '#description' => t('The file to upload.')
    );

    $form['pid'] = array(
      '#type' => 'value',
      '#value' => $pid,
    );

    $form['dsId'] = array(
      '#type' => 'value',
      '#value' => $dsId,
    );

    $form['dsLabel'] = array(
      '#type' => 'value',
      '#value' => $dsLabel,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Replace Datastream')
    );

    return $form;
  }

}