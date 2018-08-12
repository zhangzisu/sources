const axios = require('axios');

(async () => {
    const result = await axios.get('https://tieba.baidu.com/p/3357872724')
    console.log(result);
})().catch(e => console.log(e)).then(() => process.exit(0));