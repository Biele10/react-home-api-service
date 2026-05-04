import Button from "../ux/Button";
import get from "../api/crud";

function HomePageBody() {
  return (
    <div>
          <Button
            text="LED"
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
  get('led', 'power');
}

export default HomePageBody;