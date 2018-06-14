let component = ReasonReact.statelessComponent("IntegerInput");

let make = (~value, ~change, _) => {
  ...component,
  render: _ =>
    <input type_="number" value={string_of_int(value)} onChange={e => {
      let target = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e));
      change(int_of_string(target##value));
    }} />
}
