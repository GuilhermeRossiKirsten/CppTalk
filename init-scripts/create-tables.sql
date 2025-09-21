-- users
CREATE TABLE IF NOT EXISTS users (
  id SERIAL PRIMARY KEY,
  name TEXT UNIQUE NOT NULL,
  email TEXT NOT NULL UNIQUE
);

-- -- groups
-- CREATE TABLE groups (
--   id INTEGER PRIMARY KEY AUTOINCREMENT,
--   name TEXT NOT NULL
-- );

-- -- group_users
-- CREATE TABLE group_users (
--   id INTEGER PRIMARY KEY AUTOINCREMENT,
--   group_id INTEGER NOT NULL,
--   user_id INTEGER NOT NULL,
--   FOREIGN KEY(group_id) REFERENCES groups(id),
--   FOREIGN KEY(user_id) REFERENCES users(id)
-- );

-- -- messages
-- CREATE TABLE messages (
--   id INTEGER PRIMARY KEY AUTOINCREMENT,
--   group_id INTEGER NOT NULL,
--   user_id INTEGER NOT NULL,
--   content TEXT NOT NULL,
--   timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
--   FOREIGN KEY(group_id) REFERENCES groups(id),
--   FOREIGN KEY(user_id) REFERENCES users(id)
-- );
