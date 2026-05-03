import Button from "../ux/Button";
import get from "../api/crud";

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
          <Button
            text="ShutDown"
            onClickReference={ShutDown}
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
  get('pi', 'shutdown');
}

function ShutDown()
{
  get('pi', 'shutdown');
}

export default HomePageBody;