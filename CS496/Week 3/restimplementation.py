from google.appengine.ext import ndb
import webapp2
import json

def get_entity(p_id):
    return ndb.Key(urlsafe=p_id).get()		
		
class Books(ndb.Model):
	title = ndb.StringProperty()
	isbn = ndb.StringProperty()
	genre = ndb.StringProperty(repeated=True)
	author = ndb.StringProperty()
	checkedIn = ndb.BooleanProperty()

class Customers(ndb.Model):
	name = ndb.StringProperty()
	balance = ndb.FloatProperty()
	checked_out = ndb.StringProperty(repeated=True)

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.write("hello")
    def delete(self):
        ndb.delete_multi(Books.query().fetch(keys_only=True))
        ndb.delete_multi(Customers.query().fetch(keys_only=True))
		
class BooksHandler(webapp2.RequestHandler):
	def post(self):
		book_data = json.loads(self.request.body)
		new_book = Books(title=book_data['title'], 
		isbn=book_data['isbn'], 
		genre=book_data['genre'], 
		author=book_data['author'], 
		checkedIn=book_data['checkedIn'])
		new_book.put()
		
		book_dict = new_book.to_dict()
		book_dict['id'] = new_book.key.urlsafe()
		book_dict['self'] = '/books/' + new_book.key.urlsafe()
		self.response.write(json.dumps(book_dict))
		
	def get(self, id=None):
		if id:
			b = ndb.Key(urlsafe=id).get()
			b_d = b.to_dict()
			b_d['self'] = "/books/" + id
			self.response.write(json.dumps(b_d))
		elif (self.request.get('checkedIn')):
			query_value = self.request.get('checkedIn')
			if query_value == "true":
				qry = Books.query(Book.checkedIn == True)
				book_list = list()
				for items in qry:
					item_dict = items.to_dict()
					item_dict['self'] = '/books/' + items.key.urlsafe()
					book_list.append(item_dict)
				self.response.write(json.dumps(book_list))
			elif query_value == "false":
				qry = Books.query(Book.checkedIn == False)
				book_list = list()
				for items in qry:
					item_dict = items.to_dict()
					item_dict['self'] = '/books/' + items.key.urlsafe()
					book_list.append(item_dict)
				self.response.write(json.dumps(book_list))
		else:
			qry = Books.query()
			book_list = list()
			for items in qry:
				item_dict = items.to_dict()
				item_dict['id'] = items.key.id()
				item_dict['self'] = '/books/' + items.key.urlsafe()
				book_list.append(item_dict)
			self.response.write(json.dumps(book_list))
			
	def delete(self, id=None):
		if id:
			b = ndb.Key(urlsafe=id).delete()
	def patch(self, id=None):
		if id:
			b = ndb.Key(urlsafe=id).get()
			book_data = json.loads(self.request.body)
			for attribute in ['title', 'isbn', 'genre', 'author', 'checkedIn']:
				if attribute in book_data:
					setattr(b, attribute, book_data[attribute])
			b.put()
	def put(self, id=None):
		if id:
			b = ndb.Key(urlsafe=id).get()
			book_data = json.loads(self.request.body)
			if book_data.get('title'):
				b.title = book_data['title']
			else:
				b.title = None
			if book_data.get('isbn'):
				b.isbn = book_data['isbn']
			else:
				b.isbn = None
			if book_data.get('author'):
				b.author = book_data['author']
			else:
				b.author = None
			if book_data.get('genre'):
				b.genre = book_data['genre']
			else:
				b.genre = []
			if book_data.get('checkedIn'):
				b.checkedIn = book_data['checkedIn']
			else:
				b.checkedIn = None
			b.put()
			book_dict = b.to_dict()
			book_dict['id'] = b.key.id()
			book_dict['self'] = '/books/' + b.key.urlsafe()
			self.response.write(json.dumps(book_dict))

class CustomersHandler(webapp2.RequestHandler):
    def post(self):
        customers_data = json.loads(self.request.body)
        if customers_data['checked_out'] is None or customers_data['checked_out'] == '':
            customers_data['checked_out'] = ''
        new_customer = Customers(
            name=customers_data['name'],
            balance=customers_data['balance'],
            checked_out=customers_data['checked_out'])
        new_customer.put()
        customers_dict = new_customer.to_dict()
        customers_dict['id'] = new_customer.key.urlsafe()
        customers_dict['self'] = '/customers/' + new_customer.key.urlsafe()
        self.response.write(json.dumps(customers_dict))

    def get(self, id=None):
        if id:
            customer = get_entity(id)
            customer_dict = customer.to_dict()
            customer_dict['id'] = id
            customer_dict['self'] = '/customers/' + id
            self.response.write(json.dumps(customer_dict))
        else:
            query_customer = Customers.query()
            customer_list = query_customer.fetch()
            results = []
            for entity in customer_list:
                single_customer = entity.to_dict()
                single_customer['id'] = entity.key.id()
                single_customer['self'] = '/customers/' + entity.key.urlsafe()
                results.append(single_customer)
            self.response.write(json.dumps(results))

    def patch(self, id=None):
        if id:
            customer = get_entity(id)
            properties = json.loads(self.request.body)
            if 'name' in properties:
                customer.name = properties['name']
            if 'balance' in properties:
                customer.balance = properties['balance']
            if 'checked_out' in properties:
                customer.checked_out = properties['checked_out']
            customer.put()
            book_dict = customer.to_dict()
            book_dict['id'] = customer.key.id()
            book_dict['self'] = '/books/' + customer.key.urlsafe()
            self.response.write(json.dumps(book_dict))

    def delete(self, id=None):
        query_customer = get_entity(id)
        query_customer.key.delete()
			
class CheckInOut(webapp2.RequestHandler):
    def put(self, *args):
        customer_id = args[0]
        customers = get_entity(customer_id)
        book_id = args[1]
        books = get_entity(book_id)
        books.checkedIn = False
        books.put()
        customers.checked_out.append('/books/' + book_id)
        customers.put()

    def get(self, *args):
        customer_id = args[0]
        customers = get_entity(customer_id)
        book_id = args[1]
        if any(book_id in s for s in customers.checked_out):
            books = get_entity(book_id)
            book = books.to_dict()
            book['id'] = book_id
            self.response.write(json.dumps(book))

    def delete(self, *args):
        customer_id = args[0]
        customers = get_entity(customer_id)
        book_id = args[1]
        books = get_entity(book_id)
        books.checkedIn = True
        books.put()
        customers.checked_out.remove('/books/' + book_id)
        customers.put()


class CheckedOutHandler(webapp2.RequestHandler):
    def get(self, id=None):
        customer_id = id
        customer = get_entity(customer_id)
        cust_dict = customer.to_dict()
        books_checked_out = cust_dict['checked_out']
        results = []
        for book in books_checked_out:
            book = CheckedOutHandler.url_string_maker(book)
            book = get_entity(book)
            book_d = book.to_dict()
            results.append(book_d)
        self.response.write(json.dumps(results))

    @staticmethod
    def url_string_maker(book_str):
        return book_str.replace('/books/', '').replace(' ', '').replace('[', '').replace(']', '') \
            .replace('u\'', '').replace('\'', '')


			

allowed_methods	= webapp2.WSGIApplication.allowed_methods
new_allowed_methods = allowed_methods.union(('PATCH',))
webapp2.WSGIApplication.allowed_methods = new_allowed_methods


		
app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/customers/(.*)/books/(.*)', CheckInOut),
    ('/customers/(.*)/books', CheckedOutHandler),
    ('/customers', CustomersHandler),
    ('/customers/(.*)', CustomersHandler),
    ('/books', BooksHandler),
    ('/books/', BooksHandler),
    ('/books/(.*)', BooksHandler)
], debug=True)