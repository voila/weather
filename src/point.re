open Types;

let ste = ReasonReact.stringToElement;

exception NotWeekday(int);

let getDay = (d: Js.Date.t) => {
  let n = Js.Date.getDay(d) |> int_of_float;
  switch n {
  | 0 => "Sun"
  | 1 => "Mon"
  | 2 => "Tue"
  | 3 => "Wed"
  | 4 => "Thu"
  | 5 => "Fri"
  | 6 => "Sat"
  | _ => raise(NotWeekday(n))
  };
};

let string_of_date = (d: Js.Date.t) => {
  let day = getDay(d);
  let date = Js.Date.getDate(d) |> int_of_float;
  let hours = Js.Date.getHours(d) |> int_of_float;
  {j|$day $date - $(hours):00 |j};
};

let string_of_rain = r =>
  {js|💧|js}
  ++ (
    switch r {
    | Some(n) => Printf.sprintf(" %0.1f", n)
    | None => "0"
    }
  )
  ++ "mm";

let string_of_temp = t => {js|🌡|js} ++ {j| $(t)C|j};

/* let deg = 0x00B0; */
let string_of_wind = w => {js|💨|js} ++ {j| $(w)m/sec|j};

let url_of = id => {j|http://openweathermap.org/img/w/$(id).png|j};

let component = ReasonReact.statelessComponent("Point");

/* let calculateStyle = (pressure: float) : ReactDOMRe.style =>
   ReactDOMRe.Style.make(~backgroundColor=calculateDiff(pressure), ()); */
let make = (~pt: point, _children) => {
  ...component,
  render: _self => {
    let date = Js.Date.(pt.time *. 1000. |> fromFloat);
    <div>
      <div className="date"> (ste(date |> string_of_date)) </div>
      <div className="icon"> <img src=(url_of(pt.icon)) /> </div>
      <div className="summary"> (ste(pt.desc)) </div>
      <div className="temp"> (ste(pt.temp |> string_of_temp)) </div>
      <div className="rain"> (ste(pt.rain |> string_of_rain)) </div>
      <div className="wind"> (ste(pt.wind |> string_of_wind)) </div>
    </div>;
  }
};