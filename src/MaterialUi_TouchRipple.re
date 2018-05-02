module Classes = {
  type classesType =
    | Root(string)
    | Ripple(string)
    | RippleVisible(string)
    | RipplePulsate(string)
    | Child(string)
    | ChildLeaving(string)
    | ChildPulsate(string);
  type t = list(classesType);
  let to_string =
    fun
    | Root(_) => "root"
    | Ripple(_) => "ripple"
    | RippleVisible(_) => "rippleVisible"
    | RipplePulsate(_) => "ripplePulsate"
    | Child(_) => "child"
    | ChildLeaving(_) => "childLeaving"
    | ChildPulsate(_) => "childPulsate";
  let to_obj = listOfClasses =>
    listOfClasses
    |> StdLabels.List.fold_left(
         ~f=
           (obj, classType) => {
             switch (classType) {
             | Root(className)
             | Ripple(className)
             | RippleVisible(className)
             | RipplePulsate(className)
             | Child(className)
             | ChildLeaving(className)
             | ChildPulsate(className) =>
               Js.Dict.set(obj, to_string(classType), className)
             };
             obj;
           },
         ~init=Js.Dict.empty(),
       );
};

[@bs.obj]
external makeProps :
  (
    ~center: bool=?,
    ~className: string=?,
    ~classes: Js.Dict.t(string)=?,
    ~style: ReactDOMRe.Style.t=?,
    unit
  ) =>
  _ =
  "";

[@bs.module "material-ui/ButtonBase/TouchRipple"]
external reactClass : ReasonReact.reactClass = "default";

let make =
    (
      ~center: option(bool)=?,
      ~className: option(string)=?,
      ~classes: option(Classes.t)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      makeProps(
        ~center?,
        ~className?,
        ~classes=?Js.Option.map((. v) => Classes.to_obj(v), classes),
        ~style?,
        (),
      ),
    children,
  );
