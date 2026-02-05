const file = require("fs");
const exp = require("express");
const app = exp();
app.use(exp.urlencoded({extended: false}));
const port = 2004;
const users = require("./MOCK_DATA.json");

// GET

app.get("/api/users",(request,response) => {
    return response.json(users);
});

app.get("/users",(request,response) => {
    const html = `
    <ul>
        ${users.map((user) => `<li>${user.first_name}</li>`).join("")}
    </ul>
    `;
    response.send(html);
});

// ROUTING

app.route("/api/users/:id")

    // GET

    .get((request,response) => {
        const id = Number(request.params.id);
        const user = users.find((user) => user.id === id);
        return response.json(user); 
    })


    // PATCH

    .patch((request,response) => {
        const id = Number(request.params.id);
        const user = users.find((user) => user.id === id);
        return response.json(user); 
    })

    // DELETE

    .delete((request,response) => {
        const id = Number(request.params.id);
        const user = users.find((user) => user.id === id);
        return response.json(user); 
    });

// POST

app.post("/api/users",(request,response) => {
    const body = request.body;
    users.push({...body, id: users.length+1});
    file.writeFile('./MOCK_DATA.json',JSON.stringify(users),() => {
        return response.send(`Successfully done with user with id:${users.length}`); 
    });
});

// START

app.listen(port,() => {
    console.log("Ongoing");
});