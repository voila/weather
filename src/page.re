open Types;

let ste = ReasonReact.stringToElement;

/* This is the basic component. */
let component = ReasonReact.statelessComponent("Page");

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
  didMount: self => {
    let () =
      Js.Promise.(
        Api.mockForecast(1, 2)
        |> then_(jsonText => {
             let resp: points = parseJson(Js.Json.parseExn(jsonText));
             Js.log(resp);
             resolve();
           })
        |> ignore
      );
    ReasonReact.NoUpdate;
  },
  render: self => <div> (ReasonReact.stringToElement(message)) </div>
};