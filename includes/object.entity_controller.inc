<?php

/**
 * @file
 * Very basic entity controller.
 */

class IslandoraObjectEntityController implements DrupalEntityControllerInterface {

  /**
   * Constructor.
   *
   * @param string $entity_type
   *   The type of entity.
   */
  public function __construct($entity_type) {
    // No-op...
  }

  /**
   * Load all the entities.
   *
   * @param array $ids
   *   The ID's of the entities.
   * @param array $conditions
   *   The conditions to apply.
   *
   * @return array
   *   An array of loaded objects.
   */
  public function load($ids = array(), $conditions = array()) {
    if (isset($conditions['id'])) {
      // Allow loading by specifying the ID as a property as a work-around,
      // since some components dealing with entities expect IDs to be numeric.
      $ids = array_merge($ids, (array) $conditions['id']);
    }
    elseif (!empty($conditions)) {
      throw new Exception('Conditions other than "id" not implemented.');
    }

    $loaded = array();
    foreach ($ids as $id) {
      $load = islandora_object_load($id);
      if ($load) {
        $loaded[] = $load;
      }
    }

    return $loaded;
  }

  /**
   * Reset the cache.
   *
   * @param array $ids
   *   The ID's of the entities.
   */
  public function resetCache(array $ids = NULL) {
    // no-op.
  }
}
