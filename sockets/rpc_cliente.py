import xmlrpc.client

s = xmlrpc.client.ServerProxy('http://localhost:21212')
print(s.add(2,3))  # Returns 5

# Print list of available methods
print(s.system.listMethods())