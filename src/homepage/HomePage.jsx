import HomePageHeader from "./HomePageHeader";
import HomePageBody from "./HomePageBody";
import './styles.css';

function HomePage()
{
    return(
        <div className="homepage">
        <HomePageHeader/>
        <HomePageBody/>
        </div>
    )
}

export default HomePage;