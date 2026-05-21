abstract class Database {
  void query(String sql);
}

class RealDatabase extends Database {
  @override
  void query(String sql) {
    print('Executing query: $sql');
  }
}

class DatabaseProxy extends Database {
  RealDatabase? _realDatabase;
  String _currentUser;
  final Map<String, bool> _permissions = {};
  
  DatabaseProxy(this._currentUser) {
    _permissions['admin'] = true;
    _permissions['user'] = false;
    _permissions['guest'] = false;
  }
  
  bool _hasPermission() {
    return _permissions[_currentUser] ?? false;
  }
  
  @override
  void query(String sql) {
    if (_hasPermission()) {
      _realDatabase ??= RealDatabase();
      _realDatabase!.query(sql);
    } else {
      print('Access denied: User \'$_currentUser\' does not have permission to execute queries');
    }
  }
  
  void setUser(String user) {
    _currentUser = user;
  }
}
