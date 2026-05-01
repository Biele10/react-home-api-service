import Button from "../ux/Button";

function HomePageBody() {
  return (
    <div>
          <Button
            text="Click me"
            onClickReference={LedButton}
            style=
            {{
                minHeight: '100%',
                margin: '0 0 15px 0'
            }}
          />
    </div>
  );
}

function LedButton()
{
    console.log("this turns on the LED");
}

export default HomePageBody;