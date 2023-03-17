<!doctype html>
<html lang="en">

<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Praktek 2 Ultrasonik</title>
	<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
</head>

<?php
$curl_handle = curl_init();

$url = "https://api.thingspeak.com/channels/2068881/fields/1.json";

// Set the curl URL option
curl_setopt($curl_handle, CURLOPT_URL, $url);
curl_setopt($curl_handle, CURLOPT_RETURNTRANSFER, true);
$curl_data = curl_exec($curl_handle);

curl_close($curl_handle);
$response_data = json_decode($curl_data);
?>

<body>
	<div class="container mt-5">
		<div class="row">
			<div class="col-xl-12 mb-2">
				<div class="card">
					<div class="card-header">
						<h5 class="card-title">Grafik Ketinggian</h5>
					</div>
					<div class="card-body">
						<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2068881/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Grafik+Ketinggian&type=line&xaxis=Waktu&yaxis=Tinggi"></iframe>
					</div>
				</div>
			</div>
			<div class="col-xl-12">
				<div class="card">
					<div class="card-header">
						<h5 class="card-title">Data Ketinggian</h5>
					</div>
					<div class="card-body">
						<table class="table">
							<thead>
								<tr>
									<th scope="col">#</th>
									<th scope="col">Tinggi</th>
								</tr>
							</thead>
							<tbody>
								<?php foreach ($response_data->feeds as $i => $feeds) : ?><tr>
										<th scope="row"><?= $i + 1; ?></th>
										<td><?= $feeds->field1; ?></td>
									</tr>
								<?php endforeach; ?>
							</tbody>
						</table>
					</div>
				</div>
			</div>
		</div>
	</div>
	<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js" integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN" crossorigin="anonymous"></script>
</body>

</html>