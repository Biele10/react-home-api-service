import Button from "../ux/Button";
import get from "../api/crud";

function HomePageBody() {
  return (
    <div>
          <Button
            text="On Board LED"
            onClickReference={LedButton}
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

          <Button
            text="Shutdown"
            onClickReference={Shutdown}
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
  get('command', 'onBoardLedPower');
}

function RedLedButton()
{
  get('command', 'redLed', 'power');
}

function Shutdown()
{
  get('command', 'shutdown');
}

export default HomePageBody;