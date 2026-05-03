import Header from "../ux/Header";

function HomePageHeader()
{
    return(
        <Header
        text="HomeAPI"
        style={
            {marginTop: '10vh',
            minWidth: '50%'}
        }/>
    )
}

export default HomePageHeader;