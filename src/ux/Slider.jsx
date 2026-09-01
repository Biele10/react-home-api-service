// Sets the default CSS values for the slider class.
const defaultStyle = {
  marginTop: '0vh',
  minHeight: '60px',
  minWidth: '200px',
  paddingTop: '10px',
  borderStyle: 'solid',
  borderColor: 'black',
  borderRadius: '8px',
  borderWidth: '3px',
  backgroundColor: '#25b0a4',
  textAlign: 'center'
};

/**
 * Parent class for a slider.
 * Allow user to simply pass text for slider
 * and the classname of the CSS to use.
 * 
 * @param {text}: string
 * @param {styleClassName}: string
 * @returns 
 */
function Slider({style = {}, onSlideReference = null}) {

    // Takes the styles passed in and overwrites any of the default styles which
    // were defined originally
    const mergedStyles = {
        ...defaultStyle,
        ...style
    };

    return (
      <div style={mergedStyles}>
        <input onChange={onSlideReference} type="range" min="1" max="100" defaultValue="50"></input>
      </div>
    );
}

export default Slider;