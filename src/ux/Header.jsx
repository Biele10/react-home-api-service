import './../styles/index.css';

/**
 * Parent class for a header.
 * Allow user to simply pass text for header
 * and the classname of the CSS to use.
 * 
 * @param {text}: string
 * @param {styleClassName}: string
 * @returns 
 */
function Header({text, styleClassName}) {
    return (
        <div className="page_header_container">
            <div className={styleClassName}>
            <h1>{text}</h1>
            </div>
        </div>
    );
}

export default Header;