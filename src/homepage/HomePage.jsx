import HomePageHeader from "./HomePageHeader";
import HomePageBody from "./HomePageBody";
import Container from "../ux/Container";

function HomePage()
{
    return(
        <div>
        <HomePageHeader/>
        <Container style = 
        {{
            display: 'flex',
            flexDirection: 'column',
            alignItems: 'center',
            marginTop: '40px'
        }}>
        <HomePageBody/>
        </Container>
        </div>
    )
}

export default HomePage;