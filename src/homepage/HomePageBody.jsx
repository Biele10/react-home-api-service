import Button from "../ux/Button";
import get from "../api/crud";

function HomePageBody() {
  return (
    <div>
          <Button
            text="Onboard LED"
            onClickReference={OnboardLedButton}
            style=
            {{
                minHeight: '100%',
                margin: '0 0 15px 0'
            }}
          />

          <Button
            text="Red LED"
            onClickReference={RedLedButton}
            style=
            {{
                minHeight: '100%',
                margin: '0 0 15px 0'
            }}
          />
    </div>
  );
}

function OnboardLedButton()
{
  get('command', 'onboardLed', 'power');
}

function RedLedButton()
{
  get('command', 'redLed', 'power');
}

export default HomePageBody;