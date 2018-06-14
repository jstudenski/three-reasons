let component = ReasonReact.statelessComponent("IntegerInput");

let make = (~value, ~change, _) => {
  ...component,
  render: _ =>
    <input type_="number" value={string_of_int(value)} onChange={e => {
      let target = e |. ReactEventRe.Form.target |. ReactDOMRe.domElementToObj;
      change(int_of_string(target##value));
    }} />
}
