window.self = {
    close : function() {
        if(window.opener){
            window.close();
        }
    }
};