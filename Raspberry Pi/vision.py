import argparse
import base64
import json

from googleapiclient import discovery
from oauth2client.client import GoogleCredentials

def analyzeImage():
    """Run a label request on a single image"""
    credentials = GoogleCredentials.get_application_default()
    service = discovery.build('vision', 'v1', credentials=credentials)

    with open('image.jpg', 'rb') as image:
        image_content = base64.b64encode(image.read())
        service_request = service.images().annotate(body={
            'requests': [{
                'image': {
                    'content': image_content.decode('UTF-8')
                },
                'features': [{
                    'type': 'LABEL_DETECTION',
                    'maxResults': 10
                }]
            }]
        })
        response = service_request.execute()
        tags = ['person','people','human','man','woman','boy','girl','animal','dog','cat','t shirt','facial hair','shoulder','head','arm','muscle','fun','body']
        response_dict = json.loads(json.dumps(response))
        size = len(response_dict['responses'][0]['labelAnnotations'])
        subjects = []
        for i in range(0,size):
            for tag in tags:
                if response['responses'][0]['labelAnnotations'][i]['description'] == tag:
                    if tag == 'fun':
                        subjects.append('strange behaviour')
                    else:
                        subjects.append(tag)
        return subjects
       

        
