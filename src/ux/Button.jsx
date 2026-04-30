// Sets the default CSS values for the Button class.
const defaultButtonStyles = {
  minHeight: '50px',
  minWidth: '100px',
  borderStyle: 'solid',
  borderColor: 'aliceblue',
  borderRadius: '10px',
  textAlign: 'center',
  cursor: 'pointer'
};

const defaultContainerStyles = {

}

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