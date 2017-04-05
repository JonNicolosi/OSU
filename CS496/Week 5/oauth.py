from google.appengine.ext import ndb
from google.appengine.api import urlfetch
import logging
import webapp2
import json
import urllib
import random

class OauthHandler(webapp2.RequestHandler):
	def get(self):
		auth_code = self.request.get('code')
		state = self.request.get('state')
		headers = {'Content-Type': 'application/x-www-form-urlencoded'}
		parameters = {
		'code': auth_code,
		'client_id': '615979551034-bplvi74m6bspks7pm2f6h842hhbb2mnu.apps.googleusercontent.com',
		'client_secret': 'pt0aaSu5mimBIwq08m8AGJWQ',
		'redirect_uri': 'https://oauth-158418.appspot.com/oauth',
		'grant_type': 'authorization_code'
		}
		try:
			result = urlfetch.fetch(
			url='https://www.googleapis.com/oauth2/v4/token',
			payload=urllib.urlencode(parameters),
			method=urlfetch.POST,
			headers=headers
			)
			if result.status_code == 200:
				data = json.loads(result.content)
				access_token = data['access_token']
			else:
				self.response.status_code = result.status_code
		except urlfetch.Error as e:
			logging.debug(e)
			
		new_headers = {'Authorization': 'Bearer ' + access_token}
		try:
			new_result = urlfetch.fetch(
			url='https://www.googleapis.com/plus/v1/people/me',
			method=urlfetch.GET,
			headers=new_headers
			)
			if result.status_code == 200:
				new_data = json.loads(new_result.content)
				self.response.write('Display Name: ' + new_data['displayName'] + '<br>' + 'State Variable: ' + state + '<br>' + 'Google+ URL: ' + new_data['url'] + '</br>')
			else:
				self.response.status_code = result.status_code
		except urlfetch.Error:
			logging.exception('Caught exception fetching url')


class MainPage(webapp2.RequestHandler):
	def get(self):
		statelist = ['state_variable1','state_variable2','state_variable3','state_variable4','state_variable5','state_variable6']
		state = random.choice(statelist)
		url = 'https://accounts.google.com/o/oauth2/v2/auth?response_type=code&client_id=615979551034-bplvi74m6bspks7pm2f6h842hhbb2mnu.apps.googleusercontent.com&redirect_uri=https://oauth-158418.appspot.com/oauth&scope=email&state=' + state
		try:
			result = urlfetch.fetch(url)
			if result.status_code == 200:
				self.response.write(result.content)
			else:
				self.response.status_code = result.status_code
		except urlfetch.Error:
			logging.exception('Caught exception fetching url')
		
		
app = webapp2.WSGIApplication([
	('/', MainPage),
	('/oauth', OauthHandler)
], debug=True)