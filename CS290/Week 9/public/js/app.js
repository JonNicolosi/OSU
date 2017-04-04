function getId(e) {
   return $(e.target).parent('tr').data('id');
}

function makeEditForm(e, id) {
   $('.editContainer').html('');
      var form = '<h3>Edit Form</h3><form class="form-horizontal edit-form col-md-6">' + $('.post').html() + '</form>';
      $('.editContainer').append(form);
      $('.edit-form .add-task').removeClass('add-task').addClass('edit-task');
   $.ajax({
      url: '/tasks?id=' + id,
      success: function(data) {
         var obj = JSON.parse(data.results);
         var units = obj[0].units === 1 ? 'lbs' : 'kg';
         $('.edit-form .name').val(obj[0].name);
         $('.edit-form .rep').val(obj[0].rep);
         $('.edit-form .weight').val(obj[0].weight);
         $('.edit-form .date').val(obj[0].date);
         $('.edit-form .units').val(units); 
         $('.edit-form .edit-task').on('click', function(e) {
            e.preventDefault();
            var str = '';
            str += '?id=' + id;
            str += '&name=' + $('.edit-form .name').val();
            str += '&rep=' + $('.edit-form .rep').val();
            str += '&weight=' + $('.edit-form .weight').val();
            str += '&date=' + $('.edit-form .date').val();
            str += '&units=' + $('.edit-form .units').val();
            if ($.trim($('.edit-form .name').val()) !== '') {
               $.ajax({
                  method: 'PUT',
                  url: '/tasks' + str,
                  success: getData
               });
            }
         });
       }
   });       
}

function addListeners() {
   $('.delete').on('click', function(e) {
      var id = getId(e);
      $.ajax({
         url: '/tasks?id=' + id,
         method: 'DELETE',
         success: getData
      });    
   });

   $('.edit').on('click', function(e) {
      var id = getId(e);
      makeEditForm(e, id);
   });
}

function renderTable(data, textStatus, jqXHR) {
   var json = JSON.parse(data.results);
   $('.tableContainer').html('');
   
   if (json.length > 0) {
      var body = document.body;
      var table = document.createElement('table');
      var tableBody = document.createElement('tbody');

      table.style.width = '100%';
      table.setAttribute('border', '1');
      var tr = document.createElement('tr');
      for (var key in json[0]) {
         if (key !== 'id') {
            var th = document.createElement('th');
            th.appendChild(document.createTextNode(key));
            tr.appendChild(th);
         }
      }
      var th = document.createElement('th');
      tr.appendChild(th);
      tr.appendChild(th);
      tableBody.appendChild(tr);
      for (var i = 0; i < json.length; i++) {
         tr = document.createElement('tr');
         for (var k in json[i]) {
            if (k !== 'id') {
               var td = document.createElement('td');
               var label = json[i][k];
               td.appendChild(document.createTextNode(label));
               tr.appendChild(td);
            } else {
               tr.setAttribute('data-id', json[i][k]);
            }
         }
         var edit = document.createElement('button');
         edit.className = 'btn btn-default edit';
         edit.appendChild(document.createTextNode('edit'));
         var del = document.createElement('button');
         del.className = 'btn btn-danger delete';
         del.appendChild(document.createTextNode('delete'));
         tr.appendChild(edit);
         tableBody.appendChild(tr);
         tr.appendChild(del);
         tableBody.appendChild(tr); 
      }
      table.appendChild(tableBody);
      var div = document.getElementsByClassName('tableContainer')[0];
      div.appendChild(table);
   } else {
      $('.tableContainer').html('No records to show');
   }
   addListeners();
}

function getData() {
   $('.editContainer').html('');
   $.ajax({
      url: '/tasks',
      dataType: 'json',
      success: renderTable
   });
}

$(document).ready(function(){
   getData();

   $('.add-task').on('click', function(e) {
      e.preventDefault();
      var newTask = {};
      newTask['name'] = $('.name').val();
      newTask['rep'] = $('.rep').val();
      newTask['weight'] = $('.weight').val();
      newTask['date'] = $('.date').val();
      newTask['units'] = $('.units').val();
      if ($.trim(newTask['name']) !== '') {
         $.ajax({
            url: '/tasks',
            method: 'POST',
            data: newTask,
            success: getData
         });   
      }
   });       
});