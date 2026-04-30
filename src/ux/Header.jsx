import './../styles/index.css';

// Sets the default CSS values for the header class.
const defaultStyle = {
  marginTop: '10vh',
  minHeight: '60px',
  minWidth: '400px',
  borderStyle: 'solid',
  borderColor: 'aliceblue',
  borderRadius: '8px',
  backgroundColor: '#25b0a4',
  textAlign: 'center'
};

/**
 * Parent class for a header.
 * Allow user to simply pass text for header
 * and the classname of the CSS to use.
 * 
 * @param {text}: string
 * @param {styleClassName}: string
 * @returns 
 */
function Header({text, style = {}}) {

    // Takes the styles passed in and overwrites any of the default styles which
    // were defined originally
    const mergedStyles = {
        ...defaultStyle,
        ...style
    };

    return (
    <div className="page_header_container">
      <div style={mergedStyles}>
        <h1>{text}</h1>
      </div>
    </div>
  );
}

export default Header;