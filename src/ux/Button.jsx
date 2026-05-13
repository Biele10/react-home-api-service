// Sets the default CSS values for the Button class.
const defaultButtonStyles = {
  minHeight: '20%',
  maxHeight: '40%',
  minWidth: '100%',
  maxWidth: '100%',
  borderStyle: 'solid',
  borderColor: 'black',
  borderWidth: '3px',
  fontWeight: 'Bold',
  color: 'black',
  borderRadius: '10px',
  textAlign: 'center',
  margin: '0 0 0 0',
  padding: '1.5rem 3.5rem',
  cursor: 'pointer',
};

// const defaultContainerStyles = {

// }

/**
 * Base component class for a button.
 * @returns
 */
function Button({text, style = {}, containerStyle = {}, onClickReference = null, onHoverClass})
{
    const mergedButtonStyles = {
        ...defaultButtonStyles,
        ...style
    };

    return(
        <div>
            <button onClick={onClickReference} style={mergedButtonStyles}>{text}</button>
        </div>
    )
}

export default Button;