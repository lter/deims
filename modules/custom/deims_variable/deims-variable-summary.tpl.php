<details>
  <summary><?php print $name; ?></summary>
  <ul>
  <?php foreach ($details as $detail_label => $detail) { ?>
    <li><strong><?php print $detail_label; ?>:</strong> <?php print $detail; ?></li>
  <?php } ?>
  </ul>
</details>
