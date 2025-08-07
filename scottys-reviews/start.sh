#!/bin/sh

# Wait until the database is ready
echo "⏳ Waiting for the database to be ready..."
until npx prisma migrate deploy; do
  >&2 echo "Database is unavailable - sleeping"
  sleep 2
done

# Seed the database (only for dev or initial setup)
echo "🌱 Seeding the database..."
npx prisma db seed

# Start the Next.js app
echo "🚀 Starting the app..."
echo ""
echo "✅ App is running! Open your browser at:"
echo "🌐 http://localhost:3000"
echo ""
exec npm run dev