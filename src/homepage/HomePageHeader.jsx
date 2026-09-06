import Header from "../ux/Header";

function HomePageHeader()
{
    return(
        <Header
        text="Samaritan"
        style={
            {
                minWidth: '50%',
                margin: '10% 0 0 0'
            }
        }/>
    )
}

export default HomePageHeader;