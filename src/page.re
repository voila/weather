let ste = ReasonReact.stringToElement;

[@bs.val] external alert : string => unit = "alert";

type state = {data: option(Api.points)};

type action =
  | DataLoaded(Api.points)
  | PosLoaded(float, float)
  | PosError(string);

/* This is the basic component. */
let component = ReasonReact.reducerComponent("Page");

/* Your familiar handleClick from ReactJS. This mandatorily takes the payload,
   then the `self` record, which contains state (none here), `handle`, `reduce`
   and other utilities */
let handleClick = (_event, _self) => Js.log("clicked!");

/* `make` is the function that mandatorily takes `children` (if you want to use
   `JSX). `message` is a named argument, which simulates ReactJS props. Usage:

   `<Page message="hello" />`

   Which desugars to

   `ReasonReact.element(Page.make(~message="hello", [||]))` */
let make = _children => {
  ...component,
  initialState: () => {data: None},
  reducer: (action, _state) =>
    switch action {
    | DataLoaded(pts) => ReasonReact.Update({data: Some(pts)})
    | PosError(msg) =>
      alert("GeoLocation: " ++ msg);
      ReasonReact.NoUpdate;
    | PosLoaded(lat, lon) =>
      /* let lat = string_of_float(lat);
         let lon = string_of_float(lon); */
      ReasonReact.SideEffects(
        (self => Api.forecastMock(lat, lon, pts => self.send(DataLoaded(pts))))
      )
    },
  didMount: self => {
    Geo.getLocation(
      ~sendPos=(lat, lon) => self.send(PosLoaded(lat, lon)),
      ~sendErr=msg => self.send(PosError(msg))
    );
    ReasonReact.NoUpdate;
  },
  render: ({state}) =>
    <div>
      <ul>
        (
          switch state.data {
          | Some(pts) =>
            ReasonReact.arrayToElement(
              Array.map(pt => <li> <Point pt /> </li>, pts)
            )
          | None => <div> (ste("Loading data...")) </div>
          }
        )
      </ul>
    </div>
};