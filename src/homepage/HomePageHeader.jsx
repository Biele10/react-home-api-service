import Header from "../ux/Header";

function HomePageHeader()
{
    return(
        <Header
        text="HomeAPI"
        style={
            {
                minWidth: '50%',
                margin: '10% 0 0 0'
            }
        }/>
    )
}

export default HomePageHeader;