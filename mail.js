
    const nodemailer = require('nodemailer');
    let transporter = nodemailer.createTransport({
        service: 'gmail',
        auth: {
            user: 'ajayg.bathini@gmail.com',
            pass: 'senwhoxngqygrllg'
        }
    });
    let mailOptions = {
        from: 'ajayg.bathini@gmail.com',
        to: '1602-20-737-310@vce.ac.in',
        subject: 'Increased power consumption',
        text: 'Your laptop power consumption has increased 1000W'
    };
    transporter.sendMail(mailOptions, function (error, info) {
        if (error) {
            console.log(error);
        } else {
            console.log('Email sent: ' + info.response);
        }
    });
