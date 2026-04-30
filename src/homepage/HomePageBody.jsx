import Button from "../ux/Button";
import Container from "../ux/Container";

function HomePageBody()
{
    return(
        <div>
        <Container containerStyle={
            {margin: '50px 0 0 50px'}
        }>
        <Button 
        text="Click me"
        onClickReference={LedButton}
        />

        <Button
        text="Another one"
        onClickReference={null}/>
        </Container>
        </div>
    )
}

function LedButton()
{
    console.log("this turns on the LED");
}

export default HomePageBody;