const result = document.getElementById('result');
const filter = document.getElementById('filter');
const listItens = [];

getData()

async function getData() {
    const res = await fetch('https://randomuser.me/api?results=50');

    const { results } = await res.json()

    //clear result

    result.innerHTML = '';
    
    results.forEach(user => {
        const li =document.createElement('li');

        listItens.push(li)

        li.innerHTML = `
            <img src="${user.picture.large}" alt="${user.name.first}">
            <div class="user-info">
            <h4>${user.name.first} ${user.name.last}</h4>
            <p>${user.location.city}, ${user.location.country}</p>
        </div>
        `

        result.appendChild(li)
    })
}

filter.addEventListener('input', (e) => filterData(e.target.value))

function filterData(searchTerm) {
    listItens.forEach(intem => {
        if(intem.innerText.toLowerCase().includes(searchTerm.toLowerCase())) {
            intem.classList.remove('hide')
        } else {
            intem.classList.add('hide')
        }
    })
}