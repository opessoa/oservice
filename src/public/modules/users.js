class User {
    constructor(email, psw) {
      this.email = email;
      this.psw = psw;
    }
    static from(json){
        return Object.assign(new User(), json);
    }
}