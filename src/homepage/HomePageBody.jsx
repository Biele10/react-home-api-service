import Button from "../ux/Button";
import Slider from "../ux/Slider";
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

          <Slider
            style=
            {{
              minHeight: '100%',
                margin: '0 0 15px 0'
            }}
            onSlideReference={AdjustLighting}/>
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

function AdjustLighting(e)
{
  const value = Number(e.target.value);
  console.log("do something with this value for API ", value)
}

export default HomePageBody;