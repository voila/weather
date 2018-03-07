open Types;

let ste = ReasonReact.stringToElement;

type state = {data: option(points)};

type action =
  | DataLoaded(points);

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
let make = (~message, _children) => {
  ...component,
  initialState: () => {data: None},
  reducer: (action, _state) =>
    switch action {
    | DataLoaded(pts) => ReasonReact.Update({data: Some(pts)})
    },
  didMount: self => {
    let () =
      Js.Promise.(
        Api.mockForecast(1, 2)
        |> then_(jsonText => {
             /* let x = decodeDataPoint(jsonText); */
             let resp: points = parseJson(Js.Json.parseExn(jsonText));
             self.send(DataLoaded(resp));
             resolve();
           })
        |> ignore
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
              Array.of_list(List.map(pt => <li> <Point pt /> </li>, pts))
            )
          | None => <div> (ste("Loading data...")) </div>
          }
        )
      </ul>
    </div>
};