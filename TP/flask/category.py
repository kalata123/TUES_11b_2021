from database import DB


class Category:

    def __init__(self, id, name):
        self.id = id
        self.name = name

    @staticmethod
    def list_categories():
        with DB() as db:
            rows = db.execute('SELECT * FROM posts').fetchall()
            return [Category(*row) for row in rows]

    def create(self):
        with DB() as db:
            values = (self.id, self.name)
            db.execute('INSERT INTO category (id, name) VALUES (?, ?)', values)
            return self

    @staticmethod
    def find_by_post(post):
        with DB() as db:
            name = db.execute('SELECT name FROM category WHERE id = ?',
                              (post.category_id,)).fetchone()
            return name

    def categories():
        with DB() as db:
            values = db.execute('''SELECT name FROM category
                                WHERE id = *''').fetchall()
        return values
