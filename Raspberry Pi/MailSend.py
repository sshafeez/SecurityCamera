import smtplib
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email import encoders

fromaddr = 'camera@gmail.com'
toaddr = 'user@gmail.com'

def SendMail(labels):
    payload = MIMEMultipart()

    payload['From'] = fromaddr
    payload['To'] = toaddr
    payload['Subject'] = 'Security Alert'
    body = ''
    for tag in labels:
        body += tag + ", "
    body += 'was detected near your home'

    payload.attach(MIMEText(body,'plain'))
    filename = 'image.jpg'
    attachment = open('/home/pi/image.jpg','rb')

    part = MIMEBase('application','octet-stream')
    part.set_payload((attachment).read())
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', "attachment; filename= %s" % filename)

    payload.attach(part)

    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(fromaddr, 'user_email_password')
    text = payload.as_string()
    server.sendmail(fromaddr, toaddr, text)
    server.quit()

