import Header from "../ux/Header";

function HomePageHeader()
{
    return(
        <Header
        text="HomeAPI"
        style={
            {marginTop: '10vh'},
            {width: '300px'}
        }/>
    )
}

export default HomePageHeader;