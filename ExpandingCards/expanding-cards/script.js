const panels = document.querySelectorAll('.panel')

panels.forEach(panel => {
    panel.addEventListener('click',() => {
        removeActiveClaasses()
        panel.classList.add('active')
    })
})

function removeActiveClaasses() {
    panels.forEach(panel => {
        panel.classList.remove('active')
    })
}