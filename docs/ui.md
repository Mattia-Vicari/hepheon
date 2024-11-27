# UI

## UI
Requirements:
- [ ] Should have childs and method to add/remove them.
- [ ] Should have a draw method that sets the right shader_program and renders all the childs.


## Panel

Requirements:
- [x] Should be defined by position, color, and size.
- [ ] It should be able to set both size and position relatively to window size or by pixels amount.
- [x] In order to use position also an anchor point should be define between:
    - center
    - bottom, left, right, top
    - one of the angles
- [ ] Can have multiple childs.
- [ ] Should have an hide/show state.
- [ ] Should have a draw method to be rendered togheter with all the childs.


## Button 
*parent class: [Panel](#panel)*

Requirements:
- [ ] Should have an active/disabled state.
- [ ] Should have a callback triggered upon click.