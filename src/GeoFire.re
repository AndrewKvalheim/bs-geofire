open BsFirebase;

type t;

type location = (float, float);

module GeoCallbackRegistration = {
  type t;
  /* GeoCallbackRegistration.cancel()
   *
   * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geocallbackregistrationcancel */
  [@bs.send] external cancel : t => unit = "";
};

module GeoQuery = {
  type t;
  /* GeoQuery.center()
   *
   * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geoquerycenter */
  [@bs.send] external center : t => location = "";
  /* GeoQuery.radius()
   *
   * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geoqueryradius */
  [@bs.send] external radius : t => float = "";
  /* GeoQuery.updateCriteria(newQueryCriteria)
   *
   * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geoqueryupdatecriterianewquerycriteria */
  [@bs.send] external updateCriteria : (t, {. "center": location, "radius": float}) => unit = "";
  let updateCriteria = (geoQuery, ~center, ~radius) =>
    updateCriteria(geoQuery, {"center": center, "radius": radius});
  [@bs.send] external updateCenter : (t, {. "center": location}) => unit = "updateCriteria";
  let updateCenter = (geoQuery, center) => updateCenter(geoQuery, {"center": center});
  [@bs.send] external updateRadius : (t, {. "radius": float}) => unit = "updateCriteria";
  let updateRadius = (geoQuery, radius) => updateRadius(geoQuery, {"radius": radius});
  /* GeoQuery.on(eventType, callback)
   *
   * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geoqueryoneventtype-callback */
  [@bs.send]
  external on :
    (
      t,
      [@bs.string]
      [
        | `ready(unit => unit)
        | `key_entered((string, location, float) => unit)
        | `key_exited((string, location, float) => unit)
        | `key_moved((string, location, float) => unit)
      ]
    ) =>
    GeoCallbackRegistration.t =
    "";
  /* GeoQuery.cancel()
   *
   * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geoquerycancel */
  [@bs.send] external cancel : t => unit = "";
};

/* new GeoFire(firebaseRef)
 *
 * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#new-geofirefirebaseref */
[@bs.new] [@bs.module] external make : ReasonFirebase.Database.Reference.t => t = "geofire";

/* GeoFire.ref()
 *
 * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geofireref */
[@bs.send] external ref : t => ReasonFirebase.Database.Reference.t = "";

/* GeoFire.get(key)
 *
 * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geofiregetkey */
[@bs.send] external get : (t, string) => Js.Promise.t(Js.nullable(location)) = "";

/* GeoFire.set(keyOrLocations[, location])
 *
 * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geofiresetkeyorlocations-location */
[@bs.send] external set : (t, string, location) => Js.Promise.t(unit) = "";

[@bs.send] external setMany : (t, Js.Dict.t(location)) => Js.Promise.t(unit) = "set";

/* GeoFire.remove(key)
 *
 * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geofireremovekey */
[@bs.send] external remove : (t, string) => Js.Promise.t(unit) = "";

/* GeoFire.query(queryCriteria)
 *
 * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geofirequeryquerycriteria */
[@bs.send] external query : (t, {. "center": location, "radius": float}) => GeoQuery.t = "";

let query = (geoFire, ~center, ~radius) => query(geoFire, {"center": center, "radius": radius});

/* GeoFire.distance(location1, location2)
 *
 * https://github.com/firebase/geofire-js/blob/v4.1.2/docs/reference.md#geofiredistancelocation1-location2 */
[@bs.module "geofire"] external distance : (location, location) => float = "";
