Sync PostGIS for Drupal GeoField

GeoField:   http://drupal.org/project/geofield
PostGIS:    http://postgis.refractions.net

This is for Drupal 7

This module syncronizes geofield data from drupal into postGIS so you can make spatial queries, or run GeoServer with it. Drupal / MySQL remains the "Database of Record", but data is replicated into postGIS so that it is more useful.

Installation
------------

1. Create a working postGIS database. 

Generally this involves installing postgres and postgis, creating a database, adding the plpgsql language to the database, adding the spatial-columns table to the database, adding finally spatial-reference tables to the database. Exact set-up varies from distro to distro. A good guide for ubuntu can be found here: 
http://blog.smartlogicsolutions.com/2010/03/04/installing-postgis-1-5-0-on-postgresql-8-4-on-ubuntu-9-10/

2. Create your postgres user and check permissions

3. Add a 'sync_postgis' database in settings.php, e.g.:
$databases = array (
  'default' =>
  array (
    'default' =>
      array(...)
  ),
  'sync_postgis' =>
  array(
    'default' =>
    array(
      'driver' => 'pgsql',
      'database' => 'my_postgis_db',
      'username' => 'postgres',
      'password' => 'postgres',
      'host' => 'localhost',
      'port' => '',
      'prefix' => '',
    )
  )
);

4. Install the module

5. Go to admin/reports/status and check the "PostGIS Database" line, which will indicate whether the module has been able to connect to your PostGIS database. If not, check that the credentials you added in settings.php are correct, amend as appropriate and try again.

6. Go to admin/config/system/sync-postgis. At the top you can enter one or more SRIDs that will commonly be used in your spatial queries, e.g. '900913'. See "Note on SRIDs" below. Select which geofields per bundle you would like to sync. You can also choose to have the values of other fields sync'd to PostGIS, which can then be used to filter or sort by. Save configuration.

7. Go to admin/config/system/sync-postgis/db and click the button that says "Ensure PostGIS tables and indexes exist". This will create an entity table, an entity_geom table, and separate bundle tables for the bundles that you have indicated you wish to sync extra data for in the previous step.

8. If you want all relevant content to get sync'd immediately, go to admin/config/system/sync-postgis/bulk and click the button that says "Sync all PostGIS content". This will queue all relevant data to be sync'd to the PostGIS database; it will be processed on cron.

9. Now when you create or update an entity of a type and bundle that have been configured to be sync'd, its geodata and any additional fields that have been specified in the configuration will be sync'd immediately to PostGIS.

Use
---------------

So what can you do now that you have your spatial data happily syncing to postgis?

Well, below is an example where we have two node types "region" and "post". Regions contain polygons and posts are points. Posts contain a field called field_post_region, which is a node-reference to a region. Here we are using the postgis database to automatically assign posts to regions based on whether a post is spatially WITHIN a region. Cool!
NOTE: The example below assumes you also have the submodule Sync PostGIS Query enabled.

<?php
function my_module_entity_presave($entity, $type) {
  if ($type == 'node') {
    $wrapper = entity_metadata_wrapper($type, $entity);
    $bundle = $wrapper->getBundle();
    switch ($bundle) {
      case 'post':
        if (!empty($entity->sync_postgis) && isset($entity->sync_postgis['field_post_location']) && !empty($entity->sync_postgis['field_post_location'])) {
          // The sync_postgis property has been added to the entity in sync_postgis module's
          // entity_presave hook - it's an array keyed by field name and containing the
          // ids in the geometry table of the geometries that have been sync'd for that field for
          // that entity.
          $geo_ids = $entity->sync_postgis['field_post_location'];
          // Get a connection to the Sync PG Database
          $connection = sync_postgis_get_postgis_connection();
          // Initiate a query on the Sync PG Database
          $query = new syncPgQuery($connection);
          // We perform an Entity Relationship Query to find all entities that
          // have the "contains" relationship wtih our geometry, which is passed
          // in as an array of ids in the entity_geom table.
          $entities = $query->entityRelQuery('contains', $geo_ids)
            ->filterByBundle('node', 'region')
            ->execute();
          if (isset($entities['node'])) {
            $nids = array_keys($entities['node']);
            // Set the node reference field value.
            $wrapper->field_post_region->set($nids[0]);
          }
        }
        break;
    }
  }
}

Similarly, you could run queries on hook_entity_view where you find all entities that have a particular relationship, say "intersects", with the current entity. Or, you can use the Query Builder to return a string of SQL, rather than actually executing the query, that can be used as the datasource for a map layer, say in Tilestache. In this case you would want a query that returns at least the geometries of the entities that satisfy a particular set of conditions (e.g. within a particular polygon). You could also provide a feature server by having a menu callback that executes a query on the database and returns features in geojson format.


Note on SRIDs
---------------
The geometry data is stored in the "geom" column of the "entity_geom" table in PostGIS. Any geometry column must be set to a particular Spatial Reference Identifier (SRID) which specifies the coordinates system, or Spatial Reference System (SRS) being used. EPSG:4326, aka WGS 84 lon lat, is the most commonly used spatial reference system as it covers the entire globe, whereas most cover only a particular part, so Sync PostGIS uses this SRID for its geometry column. However, it is very likely that your use of the data will require transformations to other SRSs - a very common one being 900913 ("Google Mercator"). For any SRID that will commonly be used when querying the data, a functional index should be set up on the table, using the St_Transform function. These will be set up for you if you enter the required SRIDs in the box on the configuration form at admin/config/system/sync-postgis.