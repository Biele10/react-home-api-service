const defaultContainerStyles = {
  display: 'flex',
  width: '100%',
  margin: '0 0 0 0',
  height: 'auto',
  flexDirection: 'row',
  justifyContent: 'flex-start',
  alignItems: 'stretch',
  gap: '20px'
};

/**
 * Base component class for a container.
 * @param {*} param0 
 * @returns 
 */
function Container({children, style = {}})
{
  const mergedStyles = {
    ...defaultContainerStyles,
    ...style
  };

  return <div style={mergedStyles}>{children}</div>;
}

export default Container;